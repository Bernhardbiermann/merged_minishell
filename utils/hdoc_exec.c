/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:39:17 by aroux             #+#    #+#             */
/*   Updated: 2025/01/24 11:39:52 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_heredoc(t_shell *data, t_Token *current, char *delim, t_env **env)
{
	int		status;
	int		exit_status;
	int		heredoc;
	char	*hdoc_file;
	pid_t	pid;

	hdoc_file = NULL;
	if (create_hdoc_tmp(&hdoc_file) < 0)
		return (-1);
	heredoc = open(hdoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc < 0)
		error_handle(data, "failed to open heredoc file", EXIT_FAILURE, env);
	pid = fork_child_hdoc(data, env);
	if (pid == 0)
	{
		write_hdoc_in_file(data, heredoc, delim, env);
		close(heredoc);
		free(hdoc_file);
		free_shell_exit(data, env, 0);
	}
	status = 0;
	exit_status = hdoc_parent_process(heredoc, pid, status);
	current->hdoc_name = hdoc_file;
	setup_signal(INTERACTIVE);
	return (exit_status);
}

pid_t	fork_child_hdoc(t_shell *data, t_env **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_handle(data, "fork failed", EXIT_FAILURE, env);
	return (pid);
}

int	hdoc_parent_process(int heredoc, pid_t pid, int status)
{
	int		exit_status;

	setup_signal(WAIT);
	close(heredoc);
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid failed");
		exit_status = 1;
	}
	if (WIFEXITED(status))
		exit_status = 0;
	else
		exit_status = WTERMSIG(status) + 128;
	return (exit_status);
}
