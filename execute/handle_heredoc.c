/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:35:00 by aroux             #+#    #+#             */
/*   Updated: 2025/01/23 15:24:38 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile sig_atomic_t	g_signal_received;

int	exec_heredoc(t_shell *data, t_Token *current, char *delimiter, t_env **env)
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
	pid = fork();
	if (pid < 0)
		error_handle(data, "fork failed", EXIT_FAILURE, env);
	else if (pid == 0)
	{
		write_heredoc_in_file(data, heredoc, delimiter, env);
		close(heredoc);
		free(hdoc_file);
		free_shell_struct(data, env);
		// if rreceive signal exit(err_code)
		exit(0);
	}
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
	current->hdoc_name = hdoc_file;
	setup_signal(INTERACTIVE);
	return (exit_status);
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
int	create_hdoc_tmp(char **filename)
{
	int		fd;

	*filename = malloc(ft_strlen("hdoc.tmp.000") + 1);
	if (!*filename)
		return (-1);
	if (create_hdocname(*filename) != 0)
		return (-1);
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
	
	setup_signal(HEREDOC);
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
		do_expansion_in_heredocs(data, &line);
		write(heredoc, line, ft_strlen(line));
		write(heredoc, "\n", 1);
		// if i received a SIGINT, free and exit
		free(line);
	}
	setup_signal(WAIT);
}

int	create_hdocname(char *hdoc_name)
{
	int	i;

	i = 1;
	ft_memset(hdoc_name, 0, 13);
	ft_memcpy(hdoc_name, "hdoc.tmp.000", ft_strlen("hdoc.tmp.000"));
	while (i < 1000)
	{
		hdoc_name[11] = '0' + (i % 10);
		hdoc_name[10] = '0' + (i / 10);
		hdoc_name[9] = '0' + (i / 100);
		if (access(hdoc_name, F_OK) != 0)
			return (0);
		i++;
	}
	return (-1);
}
