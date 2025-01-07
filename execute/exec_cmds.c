/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:20:27 by aroux             #+#    #+#             */
/*   Updated: 2025/01/07 13:20:04 by aroux            ###   ########.fr       */
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
		printf("execute builtin function\n");
	}
	else
	{
		find_cmd_path(data, i);
		env_tab = env_to_tab(data->env);
		printf("Child %d executing command: %s\n", i, data->cmds[i].path);
		if (execve(data->cmds[i].path, data->cmds[i].cmd, env_tab) == -1) // seems to work when tested on a smaller scale
		{
			free_tab(env_tab);
			//other frees?? free_exit_shell() function to implement
			error_handle("execve failed", EXIT_FAILURE);
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
	while (i < data->nb_cmds)
	{
		// save stdin and stout, reset them at the end
		if (i != data->nb_cmds - 1 && pipe(fd) == -1)
			error_handle("pipe failed", EXIT_FAILURE);
		pid = fork();
		if (pid < 0)
			error_handle("fork failed", EXIT_FAILURE);
		else if (pid == 0)
			child_process(data, i, fd, my_env);
		else
		{
			if (data->prev_fd != -1)
				close(data->prev_fd);
			if (i != data->nb_cmds - 1)
			{
				close(fd[1]);
				data->prev_fd = fd[0];
			}
			else
				close(fd[0]);
 		//	if (i > 0)
		//	{
		//		if (dup2(fd[0], STDIN_FILENO) == -1)
		//			error_handle("dup2 failed: parent", EXIT_FAILURE);
		//		close(fd[0]);
		//	}
		}
		i++;
	}
	dup2(data->std_in, STDIN_FILENO); // restore the stdin and standard out (check if it's the right approach)
	dup2(data->std_out, STDOUT_FILENO);
	// 4.12: when child process is created and then exits, it sends back 2 values; its exit status (failure or success) 
	// and a pid_t value sent to the parent to tell it to wait or tell it the process has died (=it is finished)
	//while (wait(&status) > 0) // we execute wait as long as there are still child processes running
	//	;
	// here implement function to collect the last exit status
	while (i-- > 0)
		wait(NULL);
}


