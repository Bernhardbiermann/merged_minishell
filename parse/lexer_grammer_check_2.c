/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_grammer_check_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:55:58 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/27 16:17:33 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	gc_check_for_redir_last(t_Token **token_list)
{
	t_Token	*current;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current->next)
		current = current->next;
	if ((current->type == T_APPEND || current->type == T_INPUT || \
	current->type == T_OUTPUT || current->type == T_HEREDOC || \
	current->type == T_PIPE))
	{
		current->grammer_err = 5;
		//set_err_in_data(data, token_list, current->value, 2);
		return ;
	}
}

void	gc_check_for_double_in_out_app_here(t_Token **tok_list)
{
	t_Token	*current;
	t_Token	*next;

	if (!tok_list || !*tok_list)
		return ;
	current = *tok_list;
	while (current && current->next)
	{
		next = current->next;
		if ((current->type == T_INPUT || current->type == T_OUTPUT || \
		current->type == T_APPEND || current->type == T_HEREDOC) && \
		(next->type == T_INPUT || next->type == T_OUTPUT || \
		next->type == T_APPEND || next->type == T_HEREDOC || \
		next->type == T_PIPE))
		{
			current->grammer_err = 3;
			//set_err_in_data(data, &current, next->value, 2);
			return ;
		}
		current = current->next;
	}
}

void	gc_check_for_double_pipe(t_Token **token_list)
{
	t_Token	*current;
	t_Token	*next;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current && current->next && check_t_error(token_list) != 1)
	{
		next = current->next;
		if (current->type == T_PIPE && next->type == T_PIPE)
		{
			current->grammer_err = 4;
			//set_err_in_data(data, &current, next->value, 2);
			return ;
		}
		current = current->next;
	}
}

void	check_for_only_empty_quotes(t_Token **token_list)
{
	t_Token	*current;
	t_Token	*next;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	next = current->next;
	if ((current->type == T_S_QUOT || current->type == T_D_QUOT) && \
	next == NULL && current->value[0] == '\0')
 	{
		free(current->value);
		current->value = ft_strdup("");
		current->type = T_TEXT;
		return ;
	}
}
