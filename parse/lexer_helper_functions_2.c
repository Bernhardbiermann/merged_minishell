/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_functions_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:54:57 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/17 12:25:38 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_value(t_Token *current, char *old_key, char *value)
{
	char	*new_value;

	new_value = replace_substring(current->value, old_key, value);
	free(current->value);
	current->value = new_value;
}

void	replace_special_value(t_shell *data, t_Token *current, char *start)
{
	char	*last_exit_status;

	last_exit_status = ft_itoa(data->last_exit_status);
	if (start[1] == '?')
		replace_value(current, "$?", last_exit_status);
	else if (start[1] == '$')
		replace_value(current, "$$", "YOU'RE NOT ALLOWED TO DO THIS!");
	else if (start[1] == ' ')
		replace_value(current, "$ ", "\r ");
	else
		replace_value(current, "$", "\r");
	free(last_exit_status);
}
