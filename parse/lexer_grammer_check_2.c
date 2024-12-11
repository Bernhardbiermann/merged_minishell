/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_grammer_check_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:55:58 by bbierman          #+#    #+#             */
/*   Updated: 2024/12/11 12:27:18 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_for_pipe_in_out_app_here_last(t_Token **token_list)
{
	t_Token	*current;

	current = *token_list;
	while(current->next)
		current = current->next;
	if (current->type == T_APPEND || current->type == T_INPUT || \
	current->type == T_OUTPUT || current->type == T_HEREDOC || \
	current->type == T_PIPE)
	{
		*token_list = des_tlist_create_syntlist(token_list, current->value, 2);
		return ;
	}
}