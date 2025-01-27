/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_and_print_gc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:52:48 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/27 16:40:04 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_err_in_data(t_shell *data, char *val, int err)
{
	ft_printf("minishell: syntax error near unexpected token `%s'\n", val);
	data->last_exit_status = err;
}

static void	print_grammer_err(t_shell *data, t_Token *current, int grammer_err)
{
	if (grammer_err == 1)
		set_err_in_data(data, "unclosed quotation mark", 2);
	else if (grammer_err == 2)
		set_err_in_data(data, "newline", 2);
	else if (grammer_err == 3)
		set_err_in_data(data, current->next->value, 2);
	else if (grammer_err == 4)
		set_err_in_data(data, current->next->value, 2);
	else
		set_err_in_data(data, current->value, 2);
}

void	check_and_print_gc(t_shell *data, t_Token **tokenlist)
{
	t_Token	*current;

	current = *tokenlist;
	while (current)
	{
		if (current->grammer_err != 0)
		{
			print_grammer_err(data, current, current->grammer_err);
			return ;
		}
		current = current->next;
	}
}