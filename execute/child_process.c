/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:45:33 by aroux             #+#    #+#             */
/*   Updated: 2025/01/24 11:01:54 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* the child process:
	- checks and handles redirections 	
	- duplicates prev_fd to STDIN and closes it (if there is a prev_fd)
	- duplicates write end of pipe to STDOUT if not the last cmd and closes it
	- closes all remaining files descriptors
	- executes the command */
void	child_process(t_shell *data, int i, int *fd, t_env **env)
{
	data->cmds[i].output_fd = -1;
	if (data->prev_fd != -1)
	{
		if (dup2(data->prev_fd, STDIN_FILENO) == -1)
			error_handle(data, "dup2 failed: child input", EXIT_FAILURE, env);
		close_fd(data->prev_fd);
	}
	if (i != data->nb_cmds - 1)
		child_redir_stdout(data, fd, i, env);
	else
		last_child_redir_stdout(data, i, env);
	handle_redirections(&data->cmds[i], fd, data, env);
	close_fd(fd[1]);
	close_fd(fd[0]);
	exec_cmd(data, i, env);
}

void	child_redir_stdout(t_shell *data, int *fd, int i, t_env **env)
{
	int	saved_stdout;

	if (data->cmds[i].output_fd != -1)
	{
		saved_stdout = dup(STDOUT_FILENO);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			error_handle(data, "dup2 failed: outfile", EXIT_FAILURE, env);
		if (dup2(saved_stdout, STDOUT_FILENO) == -1)
			error_handle(data, "dup2 fail: restore STDOUT", EXIT_FAILURE, env);
		close_fd(saved_stdout);
	}
	else
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1) 
			error_handle(data, "dup2 failed: child output", EXIT_FAILURE, env);
	}
	close_fd(fd[1]);
}

void	last_child_redir_stdout(t_shell *data, int i, t_env **env)
{
	if (data->cmds[i].output_fd != -1) 
	{
		if (dup2(data->cmds[i].output_fd, STDOUT_FILENO) == -1)
			error_handle(data, "dup2 failed: last command", EXIT_FAILURE, env);
	}
}
