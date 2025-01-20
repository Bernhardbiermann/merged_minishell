/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:35:00 by aroux             #+#    #+#             */
/*   Updated: 2025/01/20 12:43:17 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_heredoc(t_shell *data, char *delimiter, t_env **env)
{
	int		fd[2];
	int		status;
	int		exit_status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_handle(data, "fork failed", EXIT_FAILURE, env);
	else if (pid == 0)
		write_heredoc_in_pipe(data, fd, delimiter, env);
	else
	{
		close(fd[1]);
		exit_status = waitpid(pid, &status, 0);
		if (exit_status != 0)
			return (1);
		data->fd_heredoc = fd[0]; // to be closed after heredoc is no longer useful, ou a refermer dans toutes les fonctions de nettoyage et free

		

//		  if (WIFEXITED(status)) {
//           printf("Child exited with status %d\n", WEXITSTATUS(status));
//        } else if (WIFSIGNALED(status)) {
//            printf("Child terminated by signal %d\n", WTERMSIG(status));
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
		line = readline("heredoc>");
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
	close(fd[1]);
}