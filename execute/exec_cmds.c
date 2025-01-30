/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:20:27 by aroux             #+#    #+#             */
/*   Updated: 2025/01/29 12:36:04 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* we first check if there is only one cmd and if it's a builtin 
(then no need for pipes), or if we have to create pipes */
void	execute(t_shell *data, t_env **my_env)
{
	if (data->nb_cmds <= 1 && data->cmds[0].cmd[0])
	{
		if (is_builtin(data, 0) == 1)
		{
			if (ft_strcmp(data->cmds[0].cmd[0], "echo") == 0)
				exec_echo(data, my_env);
			else
			{
				data->last_exit_status = 0;
				handle_redirections_builtin(&data->cmds[0], data, my_env);
				exec_builtin(data, 0, my_env);
			}
		}
		else
			exec_more_cmds(data, my_env);
	}
	else
		exec_more_cmds(data, my_env);
}

void	exec_echo(t_shell *data, t_env **env)
{
	int		fd[2];
	pid_t	pid;

	fd[0] = -1;
	fd[1] = -1;
	data->last_exit_status = 0;
	pid = fork();
	if (pid < 0)
		error_handle(data, "fork failed", EXIT_FAILURE, env);
	else if (pid == 0)
	{
		handle_redirections(&data->cmds[0], fd, data, env); 
		exec_builtin(data, 0, env);
		collect_status_free_exit(data, env);
	}
	else
	{
		add_to_pids_list(data, pid);
		wait_for_pids(data);
		if (ft_strcmp(data->cmds[0].cmd[0], "exit") == 0)
			collect_status_free_exit(data, env);
	}
}

/* This function iterates over the nb of cmds, and for each cmd:
	- pipes if it's not the last cmd
	- forks to create a child process that redirects what needs redirecting, 
	- and executes the builtin or the cmd
	parent process closes pipe ends that are not useful and waits for the 
	children to terminate */
void	exec_more_cmds(t_shell *data, t_env **my_env)
{
	int		i;
	int		fd[2];
	pid_t	pid;

	i = 0;
	data->prev_fd = -1;
	fd[0] = -1;
	fd[1] = -1;
	while (i < data->nb_cmds)
	{
		if (i != data->nb_cmds - 1 && pipe(fd) == -1)
			error_handle(data, "pipe failed", EXIT_FAILURE, my_env);
		setup_signal(CHILD);
		pid = fork();
		if (pid < 0)
			error_handle(data, "fork failed", EXIT_FAILURE, my_env);
		else if (pid == 0)
		{
			child_process(data, i, fd, my_env);
		}
		else
			parent_process(data, i, fd, pid);
		i++;
	}
	wait_for_pids(data);
}

/* executes each command
	if it's a builtin, executes it and then cleans and exits
	if it's not, check for a valid path, and execve() exits and cleans */
void	exec_cmd(t_shell *data, int i, t_env **env)
{
	char	**env_tab;

	if (!data->cmds[i].cmd[0])
	{
		free_shell_struct(data, env);
		exit(EXIT_SUCCESS);
	}
	if (is_builtin(data, i) == 1)
	{
		exec_builtin(data, i, env);
		free_shell_struct(data, env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		find_cmd_path(data, i, env);
		if (find_cmd_path(data, i, env) == 0 || data->cmds[i].cmd[0][0] == '\0')
			error_cmd_file_dir(data, i, env);
		env_tab = env_to_tab(data->env);
		if (execve(data->cmds[i].path, data->cmds[i].cmd, env_tab) == -1)
		{
			free_tab(env_tab);
			error_cmd_file_dir(data, i, env);
		}
	}
}

void	parent_process(t_shell *data, int i, int *pipe, pid_t pid)
{
	add_to_pids_list(data, pid);
	if (data->prev_fd != -1)
		close_fd(data->prev_fd);
	if (i != data->nb_cmds - 1)
	{
		close_fd(pipe[1]);
		data->prev_fd = pipe[0];
	}
	else
		close_fd(pipe[0]);
}
