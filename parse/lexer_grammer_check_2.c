/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_grammer_check_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:55:58 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/22 13:04:28 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	gc_check_for_redir_last(t_shell *data, t_Token **token_list)
{
	t_Token	*current;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current->next)
		current = current->next;
	if (current->type == T_APPEND || current->type == T_INPUT || \
	current->type == T_OUTPUT || current->type == T_HEREDOC || \
	current->type == T_PIPE)
	{
		set_err_in_tokenlist(data, token_list, current->value, 2);
		return ;
	}
}

void	gc_check_for_double_in_out_app_here(t_shell *data, t_Token **token_list)
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
		(next->type == T_INPUT || next->type == T_OUTPUT || \
		next->type == T_APPEND || next->type == T_HEREDOC || \
		next->type == T_PIPE))
		{
			set_err_in_tokenlist(data, &current, next->value, 2);
			return ;
		}
		current = current->next;
	}
}

void	gc_check_for_double_pipe(t_shell *data, t_Token **token_list)
{
	t_Token	*current;
	t_Token	*next;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current && current->next)
	{
		next = current->next;
		if (current->type == T_PIPE && next->type == T_PIPE)
		{
			set_err_in_tokenlist(data, &current, next->value, 2);
			return ;
		}
		current = current->next;
	}
}