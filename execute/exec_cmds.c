/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:20:27 by aroux             #+#    #+#             */
/*   Updated: 2025/01/09 17:35:21 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* we first check if there is only one cmd, or if we have to create pipes in case of more cmds */
void	execute(t_shell *data, t_env **my_env)
{
	if (data->nb_cmds <= 1 && is_builtin(data, 0) == 1)
		exec_cmd(data, 0, my_env);
	else
		exec_more_cmds(data, my_env);
}

/* executes each command
	if it's a builtin, executes it and then has to clean and exit
	if it's not, check for a valid path, and execve() exits and cleans */
void	exec_cmd(t_shell *data, int i, t_env **my_env)
{
	char	**env_tab;

	if (is_builtin(data, i) == 1)
	{
		exec_builtin(data, i, my_env);
		if (data->nb_cmds > 1 || is_builtin(data, 0) == 0)
		{
			free_shell_struct(data, my_env);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		find_cmd_path(data, i, my_env);
		if (find_cmd_path(data, i, my_env) == 0)
			error_cmd_notfound(data, i, my_env);
		env_tab = env_to_tab(data->env);
		if (execve(data->cmds[i].path, data->cmds[i].cmd, env_tab) == -1)
		{
			free_tab(env_tab);
			error_handle(data, "execve failed", EXIT_FAILURE, my_env);
		}
	}
}

void	exec_last_cmd(t_shell *data, t_env **my_env)
{
	char	**env_tab;
	int		i;

	i = data->nb_cmds - 1;
	if (is_builtin(data, i) == 1)
	{
		exec_builtin(data, i, my_env);
		if (data->nb_cmds > 1 || is_builtin(data, 0) == 0)
		{
			free_shell_struct(data, my_env);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		find_cmd_path(data, i, my_env);
		if (find_cmd_path(data, i, my_env) == 0)
			error_cmd_notfound(data, i, my_env);
		env_tab = env_to_tab(data->env);
		if (execve(data->cmds[i].path, data->cmds[i].cmd, env_tab) == -1)
		{
			free_tab(env_tab);
			error_handle(data, "execve failed", EXIT_FAILURE, my_env);
		}
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
	int		n;
	int		fd[2];
	pid_t	pid;
	//int		status;

	i = 0;
	n = data->nb_cmds - 1;
	data->prev_fd = -1;
	fd[0] = -1; // important to initialize otherwise it's getting messed up when command not found
	fd[1] = -1;
	while (i < data->nb_cmds - 1)
	{
		if (i != data->nb_cmds - 1 && pipe(fd) == -1)
			error_handle(data, "pipe failed", EXIT_FAILURE, my_env);
		pid = fork();
		if (pid < 0)
			error_handle(data, "fork failed", EXIT_FAILURE, my_env);
		else if (pid == 0)
			child_process(data, i, fd, my_env);
		else
		{
			if (data->prev_fd != -1)
				close_fd(data->prev_fd);
			if (i != data->nb_cmds - 1)
			{
				close_fd(fd[1]);
				data->prev_fd = fd[0];
			}
			else
				close_fd(fd[0]);
		}
		i++;
	}
	//wait_for_pids(data, data->nb_cmds - 1);
	while (i-- > 0)
		wait(NULL);
	//last_child_process();
 	pid = fork();
	if (pid < 0)
		error_handle(data, "fork failed", EXIT_FAILURE, my_env);
	else if (pid == 0)
		child_process(data, n, fd, my_env);
	else
	{
		if (data->prev_fd != -1)	
			close_fd(data->prev_fd);
		close_fd(fd[0]);
	}
	wait(NULL);
	/* if (wait(&status) > 0)
	{
		if (WIFEXITED(status)) // check if process exited normally
			data->last_exit_status = WEXITSTATUS(status);
		else
			data->last_exit_status = -1;
	} */
	// 4.12: when child process is created and then exits, it sends back 2 values; its exit status (failure or success) 
	// and a pid_t value sent to the parent to tell it to wait or tell it the process has died (=it is finished)
	//while (wait(&status) > 0) // we execute wait as long as there are still child processes running
	//	;
	// here implement function to collect the last exit status

}

int	wait_for_pids(t_shell *data, int nb_cmds)
{
	int	i;
	int	status;
	int	last_exit_status;

	i = nb_cmds;
	last_exit_status = 0;
	while (i-- > 0)
	{
		if (wait(&status) > 0)
		{
			if (WIFEXITED(status)) // check if process exited normally
				last_exit_status = WEXITSTATUS(status);
			else
				last_exit_status = -1;
		}
	}
	data->last_exit_status = last_exit_status;
	return (last_exit_status);
}


