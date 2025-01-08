/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_ENV2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:29:51 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/07 17:06:08 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_last_error_status(t_shell *data, t_Token *current)
{
	char	*last_exit_status;

	last_exit_status = ft_itoa(data->last_exit_status);
	if ((current->value[0] = '?'))
	{
		replace_value(current, "?", last_exit_status);
	}
	else
	{
		free(current->value);
		current->value = ft_strdup("");
	}
	current->length = ft_strlen(current->value);
	free(last_exit_status);
}