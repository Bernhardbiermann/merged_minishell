/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_create_heredoc_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:25:29 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/14 16:39:41 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	grammer_check(t_Token *current)
{
	t_Token	*next;

	next = current->next;
	if (current && current->next)
	{
		if ((current->type == T_INPUT || current->type == T_OUTPUT || \
		current->type == T_APPEND || current->type == T_HEREDOC || \
		current->type == T_PIPE) && (next->type == T_INPUT || \
		next->type == T_OUTPUT || next->type == T_APPEND || \
		next->type == T_HEREDOC || next->type == T_PIPE))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

void	create_hdoc_list(t_shell *data, t_Token **token_list)
{
	t_Token	*current;
	t_Token	*token;

	token = NULL;
	current = *token_list;
	while (current && grammer_check(current) == 0)
	{
		if (current->type == T_HEREDOC)
		{
			merge_two(current, current->next, T_HEREDOC);
			token = new_token(current->value, T_HEREDOC, ft_strlen(current->value));
			concatenate_token(token, data->hdoc);
			delete_node_and_glue(current, token_list);
		}
		current = current->next;
	}
}