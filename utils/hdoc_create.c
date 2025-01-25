/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:39:02 by aroux             #+#    #+#             */
/*   Updated: 2025/01/25 12:04:20 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	write_hdoc_in_file(t_shell *data, int hdoc, char *delim, t_env **env)
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
			ft_printf("warning: here-document delimited by end-of-file (wanted\
 `%s')\n", delim);
			break ;
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		line = do_expansion_in_heredocs(data, &line);
		write(hdoc, line, ft_strlen(line));
		write(hdoc, "\n", 1);
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
