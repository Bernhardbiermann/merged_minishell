/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_grammer_check_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:55:58 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/15 14:04:12 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_for_pipe_in_out_app_here_last(t_Token **token_list)
{
	t_Token	*current;

	if (!token_list || !*token_list)
		return ;
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

void	check_for_double_in_out_app_here(t_Token **token_list)
{
	t_Token	*current;
	t_Token	*next;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current && current->next)
	{
		next = current->next;
		if ((current->type == T_INPUT || current->type == T_OUTPUT || \
		current->type == T_APPEND || current->type == T_HEREDOC) && \
		(next->type == T_INPUT || next->type == T_OUTPUT || next->type == \
		T_APPEND || next->type == T_HEREDOC || next->type == T_PIPE))
		{
			*token_list = des_tlist_create_syntlist(token_list, next->value, 2);
			return ;
		}
		current = current->next;
	}
}