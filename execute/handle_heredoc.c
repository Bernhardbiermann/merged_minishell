/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:35:00 by aroux             #+#    #+#             */
/*   Updated: 2025/01/21 17:36:20 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_heredoc(t_shell *data, t_redir *redir, char *delimiter, t_env **env)
{
	int		status;
	//int		exit_status;
	int		heredoc;
	char	*hdoc_file;
	pid_t	pid;

	hdoc_file = NULL;
	if (create_hdoc_tmp(&hdoc_file, redir) < 0)
		return (-1);
	heredoc = open(hdoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc < 0)
		error_handle(data, "failed to open heredoc file", EXIT_FAILURE, env);
	pid = fork();
	if (pid < 0)
		error_handle(data, "fork failed", EXIT_FAILURE, env);
	else if (pid == 0)
	{
		write_heredoc_in_file(data, heredoc, delimiter, env);
		close(heredoc);
		free(hdoc_file);
		exit(0);
	}
	close(heredoc);
	if (waitpid(pid, &status, 0) == -1)
		error_handle(data, "waitpid failed", EXIT_FAILURE, env);

	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
		error_handle(data, "heredoc child process failed", EXIT_FAILURE, env);
	redir->filename = hdoc_file;
	return (0);
}
/* testing chatGPT's version */
/* int create_hdoc_tmp(char **filename, t_redir *redir)
{
	int 	fd;
	char	*unique_suffix;

	// Generate a unique suffix based on redir's memory address
	unique_suffix = ft_itoa((uintptr_t)redir); // Or any unique identifier
	if (!unique_suffix)
		return (1);

	// Allocate memory for filename and build the unique name
	*filename = malloc(ft_strlen("hdoc_") + ft_strlen(unique_suffix) + 1);
	if (!*filename)
	{
		free(unique_suffix);
		return (1);
	}
	ft_strlcpy(*filename, "hdoc_", ft_strlen("hdoc_") + 1);
	ft_strlcat(*filename, unique_suffix, ft_strlen("hdoc_") + ft_strlen(unique_suffix) + 1);
	free(unique_suffix);

	// Create the file with the unique name
	fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("hdoc failed to open");
		free(*filename);
		return (-1);
	}
	close(fd);
	return (0);
} */

/* We create a temporary file named hdoc.tmp */
 int	create_hdoc_tmp(char **filename, t_redir *redir)
{
	int		fd;

	if (!redir)
		return (-1);
	*filename = malloc(ft_strlen("hdoc.tmp") + 1);
	if (!*filename)
		return (1);
	ft_strlcpy(*filename, "hdoc.tmp", ft_strlen("hdoc.tmp"));
	if (access(*filename, F_OK) == 0)
		unlink(*filename);
	fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("hdoc failed to open");
		free(*filename);
		return (-1);
	}
	close(fd);
	return (0);
} 

void	write_heredoc_in_file(t_shell *data, int heredoc, char *delimiter, t_env **env)
{
	char	*line;
	
	//setup_signal(HEREDOC);
	if (!env && !data)
		return ;
	while (1)
	{
		line = readline("hdoc> ");
		if (!line)
		{
			write(2, "warning: here-document delimited by end-of-file\n", ft_strlen("warning: here-document delimited by end-of-file\n"));
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(heredoc, line, ft_strlen(line));
		write(heredoc, "\n", 1);
		free(line);
	}
	//setup_signal(INTERACTIVE);
}