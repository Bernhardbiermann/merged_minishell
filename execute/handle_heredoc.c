/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:35:00 by aroux             #+#    #+#             */
/*   Updated: 2025/01/20 17:28:12 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_heredoc(t_shell *data, t_redir *redir, char *delimiter, t_env **env)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (pipe(fd) == -1)
		error_handle(data, "pipe failed in hdoc", EXIT_FAILURE, env);
	printf("Pipe created: fd[0] = %d, fd[1] = %d\n", fd[0], fd[1]);
	pid = fork();
	if (pid < 0)
		error_handle(data, "fork failed", EXIT_FAILURE, env);
	else if (pid == 0)
		write_heredoc_in_pipe(data, fd, delimiter, env);
	else 
	{
		close(fd[1]);
		/* exit_status = waitpid(pid, &status, 0);
		if (exit_status != 0)
			return (1);
		data->fd_heredoc = fd[0]; // to be closed after heredoc is no longer useful, ou a refermer dans toutes les fonctions de nettoyage et free
 */
		if (waitpid(pid, &status, 0) == -1) //wait for child process to finish
			error_handle(data, "waitpid failed", EXIT_FAILURE, env);
		if (!WIFEXITED(status)) //check exit status of the child
			error_handle(data, "heredoc child process did not exit normally", EXIT_FAILURE, env);
		if (WEXITSTATUS(status) != 0) //check exit status of the child process
			error_handle(data, "heredoc child process returned error", 1, env);

	//	data->fd_heredoc = fd[0];
		if (redir->last_redir_in == 1)
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
				error_handle(data, "dup2 failed for hdoc redirection", 1, env);	
		}
		close_fd(fd[0]);
	}
	return (0);
}

void	write_heredoc_in_pipe(t_shell *data, int *fd, char *delimiter, t_env **env)
{
	char	*line;
	
	close(fd[0]);
	if (!env && !data)
		return ;
	while (1)
	{
		line = readline("hdoc> ");
		if (!line)
		{
			// print weird warning in case CTRL + D
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
	}
	printf("Child writing to fd[1]: %d\n", fd[1]);
	close(fd[1]);
}