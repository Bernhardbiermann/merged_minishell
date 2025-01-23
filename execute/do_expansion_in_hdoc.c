/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_expansion_in_hdoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:19:02 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/23 16:17:33 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	replace_special_value_hdoc(t_shell *data, char **line, char *start);
static void	replace_value_hdoc(char **line, char *old_key, char *value);
static void	find_key_and_exchange_value_hdoc(t_shell *data, char *s,\
 char **line);
static void	find_mask_and_exchange_hdoc(char **line);

void	do_expansion_in_heredocs(t_shell *data, char **line)
{
	char	*s;

	while (ft_strchr(*line, '$') != NULL)
	{
		s = ft_strchr(*line, '$');
		while (s)
		{
			if (s[1] == '?' || s[1] == '$' || s[1] == ' ' || s[1] == '\0')
				replace_special_value_hdoc(data, line, s);
			else
				find_key_and_exchange_value_hdoc(data, *line, &s);
			s = ft_strchr(*line, '$');
		}		
		if (ft_strchr(*line, '\r') != NULL)
			find_mask_and_exchange_hdoc(line);
	}
}

static void	replace_special_value_hdoc(t_shell *data, char **line, char *start)
{
	char	*last_exit_status;

	last_exit_status = ft_itoa(data->last_exit_status);
	if (start[1] == '?')
		replace_value_hdoc(line, "$?", last_exit_status);
	else if (start[1] == '$')
		replace_value_hdoc(line, "$$", "YOU'RE NOT ALLOWED TO DO THIS!");
	else if (start[1] == ' ')
		replace_value_hdoc(line, "$ ", "\r ");
	else
		replace_value_hdoc(line, "$", "\r");
	free(last_exit_status);
}

static void	replace_value_hdoc(char **line, char *old_key, char *value)
{
	char *new_value;

	new_value = replace_substring(*line, old_key, value);
	free(*line);
	*line = new_value;
}

static void	find_key_and_exchange_value_hdoc(t_shell *data, char *s, char **line)
{
	char	*key;
	char	*old_key;
	char	*value;
	char	*end;

	end = find_end(s + 1);
	key = ft_strncpy(*line, s + 1, end);
	old_key = ft_strncpy(*line, s, end);
	value = compare_key_and_get_value(data->env, key);
	replace_value_hdoc(line, old_key, value);
	three_frees(key, old_key, value);
}

static void	find_mask_and_exchange_hdoc(char **line)
{
	char	*start;

	start = ft_strchr(*line, '\r');
	while (start)
	{
		replace_value_hdoc(line, "\r", "$");
		start = ft_strchr(*line, '\r');
	}
}
