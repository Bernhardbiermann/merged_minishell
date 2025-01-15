/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_create_heredoc_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:25:29 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/15 11:19:24 by bbierman         ###   ########.fr       */
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
		current->type == T_APPEND || current->type == T_HEREDOC) && \
		(next->type == T_INPUT || next->type == T_OUTPUT || \
		next->type == T_APPEND || next->type == T_HEREDOC || \
		next->type == T_PIPE))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

t_hdoc	*new_hdoc_token(char *value)
{
	t_hdoc	*new_token;

	new_token = malloc(sizeof(t_hdoc));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	return (new_token);
}

t_hdoc	*concatenate_hdoc_token(t_hdoc *new_token, t_hdoc **token_list)
{
	t_hdoc	*current;

	if (new_token)
	{
		if (!(*token_list))
			*token_list = new_token;
		else
		{
			current = *token_list;
			while (current->next)
				current = current->next;
			current->next = new_token;
		}
	}
	return (*token_list);
}

t_hdoc	*create_hdoc_list(t_shell *data, t_Token **token_list)
{
	t_Token	*current;
	t_Token	*next;
	t_hdoc	*token;
	t_hdoc	*hdoc_list;

	next = NULL;
	current = *token_list;
	hdoc_list = NULL;
	while (current && current->next && grammer_check(current) == 0)
	{
		if (current->type == T_HEREDOC)
		{
			next = current->next->next;
			token = new_hdoc_token(current->next->value);
			hdoc_list = concatenate_hdoc_token(token, &data->hdoc);
			merge_two(current, current->next, T_HEREDOC);
			delete_node_and_glue(current, token_list);
			current = next;
		}
		else
			current = current->next;
	}
	return (hdoc_list);
}
