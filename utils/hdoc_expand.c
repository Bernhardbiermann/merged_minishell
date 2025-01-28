/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:19:02 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/28 10:41:43 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*replace_special_val_hdoc(t_shell *data, char **line, char *start);
static char	*replace_value_hdoc(char **line, char *old_key, char *value);
static char	*find_key_and_exchange_val_hdoc(t_shell *data, char *s, \
	char **line);
static char	*replace_substring_hdoc(char **ori, char *to_replace, char *new);

char	*do_expansion_in_heredocs(t_shell *data, char **line)
{
	char	*s;

	s = ft_strchr(*line, '$');
	if (ft_strchr(*line, '$') != NULL)
	{
		while (s != NULL)
		{
			if (s[1] == '?' || s[1] == '$' || s[1] == ' ' || s[1] == '\0')
				*line = replace_special_val_hdoc(data, line, s);
			else
				*line = find_key_and_exchange_val_hdoc(data, s, line);
			s = ft_strchr(*line, '$');
		}
		s = ft_strchr(*line, '\r');
		if (ft_strchr(*line, '\r') != NULL)
		{
			while (s != NULL)
			{
				*line = replace_value_hdoc(line, "\r", "$");
				s = ft_strchr(*line, '\r');
			}
		}
	}
	return (*line);
}

static char	*replace_special_val_hdoc(t_shell *data, char **line, char *start)
{
	char	*last_exit_status;
	char	*new_value;

	last_exit_status = ft_itoa(data->last_exit_status);
	if (start[1] == '?')
		new_value = replace_value_hdoc(line, "$?", last_exit_status);
	else if (start[1] == '$')
		new_value = replace_value_hdoc(line, "$$", "THIS IS NOT ALLOWED!");
	else if (start[1] == ' ')
		new_value = replace_value_hdoc(line, "$ ", "\r ");
	else
		new_value = replace_value_hdoc(line, "$", "\r");
	free(last_exit_status);
	return (new_value);
}

static char	*replace_value_hdoc(char **line, char *old_key, char *value)
{
	char	*new_value;

	if (!line || !*line || !*old_key)
		return (NULL);
	new_value = replace_substring_hdoc(line, old_key, value);
	if (!new_value)
		return (NULL);
	free(*line);
	line = &new_value;
	return (new_value);
}

static char	*find_key_and_exchange_val_hdoc(t_shell *data, char *s, char **line)
{
	char	*key;
	char	*old_key;
	char	*value;
	char	*end;
	char	*new_line;

	end = find_end(s + 1);
	key = ft_strncpy(*line, s + 1, end);
	old_key = ft_strncpy(*line, s, end);
	value = compare_key_and_get_value(data->env, key);
	new_line = replace_value_hdoc(line, old_key, value);
	three_frees(key, old_key, value);
	return (new_line);
}

static char	*replace_substring_hdoc(char **ori, char *to_replace, char *new)
{
	char	*position;
	char	*new_str;
	size_t	to_replace_len;
	size_t	new_range;
	size_t	prefix_len;

	if (!ori || !*ori || !to_replace || !new)
		return (NULL);
	to_replace_len = ft_strlen(to_replace);
	position = ft_strstr(*ori, to_replace);
	if (!position)
		return (*ori);
	new_range = ft_strlen(*ori) - to_replace_len + ft_strlen(new);
	new_str = malloc(sizeof(char) * (new_range + 1));
	if (!new_str)
		return (NULL);
	prefix_len = position - *ori;
	ft_memcpy(new_str, *ori, prefix_len);
	ft_memcpy(new_str + prefix_len, new, ft_strlen(new));
	ft_memcpy(new_str + prefix_len + ft_strlen(new), position + \
	to_replace_len, ft_strlen(*ori) - prefix_len - to_replace_len);
	new_str[new_range] = '\0';
	return (new_str);
}
