/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:17:15 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/14 14:04:04 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_Token	*new_token(char *input, t_TokenType type, size_t length)
{
	t_Token	*new_token;

	new_token = malloc(sizeof(t_Token));
	if (!new_token)
		return (NULL);
	new_token->value = input;
	new_token->type = type;
	new_token->length = length;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

t_Token	*concatenate_token(t_Token *new_token, t_Token **token_list)
{
	t_Token	*current;

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
			new_token->prev = current;
		}
	}
	return (*token_list);
}

t_Token	*tokenize_input(char *input)
{
	t_Token	*token_list;
	t_Token	*new_token;
	int		i;

	i = 0;
	token_list = NULL;
	while (input[i])
	{
		new_token = NULL;
		if (input[i] == ' ')
			i += space_token(input + i, &new_token);
		else if (input[i] == '"' || input[i] == '\'')
			i += quote_token(input + i, &new_token);
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			i += operator_token(input + i, &new_token);
		else if (input[i] == '$')
			i += env_token(input + i, &new_token);
		else
			i += value_token(input + i, &new_token);
		token_list = concatenate_token(new_token, &token_list);
	}
	return (token_list);
}
