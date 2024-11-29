/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:37:49 by aroux             #+#    #+#             */
/*   Updated: 2024/09/19 16:13:34 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	is_newline_lenline(char *s)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
	{
		if (*s == '\n')
			return (len + 1);
		s++;
		len++;
	}
	return (0);
}

char	*join_free(char *stash, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(stash, buffer);
	free(stash);
	return (temp);
}

char	*clean_stash(char *str)
{
	char	*clean_stash;
	int		lentoremove;

	lentoremove = 0;
	while (str[lentoremove] != '\n' && str[lentoremove] != '\0')
		lentoremove++;
	lentoremove++;
	clean_stash = ft_substr(str, lentoremove, ft_strlen(str) - lentoremove);
	free(str);
	return (clean_stash);
}

char	*read_and_stash(int fd, char **stash, char *buffer, ssize_t *bytes_read)
{
	char		*line;

	line = NULL;
	*bytes_read = 1;
	if (*stash && is_newline_lenline(*stash) != 0)
	{
		line = ft_substr(*stash, 0, is_newline_lenline(*stash));
		*stash = clean_stash(*stash);
		return (line);
	}
	while (*bytes_read > 0)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read <= 0)
			break ;
		buffer[*bytes_read] = '\0';
		*stash = join_free(*stash, buffer);
		if (is_newline_lenline(buffer) != 0)
		{
			line = ft_substr(*stash, 0, is_newline_lenline(*stash));
			*stash = clean_stash(*stash);
			break ;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	ssize_t		bytes_read;
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (buffer == NULL)
		return (NULL);
	line = read_and_stash(fd, &stash, buffer, &bytes_read);
	free(buffer);
	if ((bytes_read == 0 && stash != NULL) || bytes_read < 0)
	{
		if (bytes_read == 0 && stash != NULL && *stash != '\0')
			line = ft_strdup(stash);
		free(stash);
		stash = NULL;
		if (bytes_read < 0)
			return (NULL);
	}
	return (line);
}
