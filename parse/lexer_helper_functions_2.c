/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper_functions_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:54:57 by bbierman          #+#    #+#             */
/*   Updated: 2024/12/11 12:30:09 by bbierman         ###   ########.fr       */
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

void	replace_special_value(t_Token *current, char *start)
{
	if (start[1] == '?')
		replace_value(current, "$?", "0");
	else if (start[1] == '$')
		replace_value(current, "$$", "YOU'RE NOT ALLOWED TO DO THIS!");
	else if (start[1] == ' ')
		replace_value(current, "$ ", "\r ");
	else
		replace_value(current, "$", "\r");
}