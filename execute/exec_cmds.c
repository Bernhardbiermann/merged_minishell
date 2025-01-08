/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:20:27 by aroux             #+#    #+#             */
/*   Updated: 2025/01/08 17:36:23 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* 4.12: we first check if there is only one cmd, or if we have to create pipes in case of more cmds */
void	execute(t_shell *data, t_env **my_env)
{
	if (data->nb_cmds <= 1 && is_builtin(data, 0) == 1) // if there is only one cmd and it is a builtin, we execute it. If it's not a builtin, we have to create a child process
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
		//printf("execute builtin function\n");
	}
	else
	{
		find_cmd_path(data, i, my_env);
		if (find_cmd_path(data, i, my_env) == 0)
			error_handle(data, "command not found", 0, my_env);
		// if no command path, clean fds, clean struct, exit with exit code 
		env_tab = env_to_tab(data->env);
		//printf("Child %d executing command: %s\n", i, data->cmds[i].path);
		if (execve(data->cmds[i].path, data->cmds[i].cmd, env_tab) == -1) // seems to work when tested on a smaller scale
		{
			free_tab(env_tab);
			error_handle(data, "execve failed", EXIT_FAILURE, my_env);
		}
	}
}

/* This function iterates over the nb of cmds, and for each cmd:
	pipes if it's not the last cmd
	forks to create a child process that redirects what needs redirecting, and executes the builtin or the cmd
	parent process closes pipe ends that are not useful and waits for the children to terminate

	At the moment: not working, I'm getting messages about dup2 that failed which I could not fix,
	but the pipe logic worked at some point. Need to implement the redirection logic and then work from here.
*/
void	exec_more_cmds(t_shell *data, t_env **my_env)
{
	int		i;
	int		fd[2];
	pid_t	pid;
	//int		status;

	i = 0;
	data->prev_fd = -1;
	fd[0] = -1; // important to initialize otherwise it's getting messed up when command not found
	fd[1] = -1;
	while (i < data->nb_cmds)
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
	// 4.12: when child process is created and then exits, it sends back 2 values; its exit status (failure or success) 
	// and a pid_t value sent to the parent to tell it to wait or tell it the process has died (=it is finished)
	//while (wait(&status) > 0) // we execute wait as long as there are still child processes running
	//	;
	// here implement function to collect the last exit status
	while (i-- > 0)
		wait(NULL);
}




