/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_lexer_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:30:30 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/17 12:41:25 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_Token	*delete_node_and_glue(t_Token *target, t_Token **token_list)
{
	t_Token	*temp;

	temp = NULL;
	if (!target || !token_list || !*token_list)
		return (NULL);
	if (target->prev == NULL)
	{
		*token_list = target->next;
		if (target->next)
			target->next->prev = NULL;
	}
	else
	{
		target->prev->next = target->next;
		if (target->next)
			target->next->prev = target->prev;
	}
	temp = target;
	target = target->next;
	if (temp->value)
		free(temp->value);
	free(temp);
	return (target);
}

void	delete_empty_env_and_quote(t_Token **token_list)
{
	t_Token	*current;
	t_Token	*next;

	current = *token_list;
	next = NULL;
	while (current)
	{
		next = current->next;
		if (current->type == T_ENV && current->value[0] == '\0')
			current = delete_node_and_glue(current, token_list);
		else if ((current->type == T_D_QUOT || current->type == T_S_QUOT) \
		&& current->value[0] == '\0')
			current = delete_node_and_glue(current, token_list);
		else
			current = next;
	}
}

void	delete_spaces(t_Token **token_list)
{
	t_Token	*current;
	t_Token	*next;

	current = *token_list;
	next = NULL;
	while (current)
	{
		next = current->next;
		if (current->type == T_SPACE)
			current = delete_node_and_glue(current, token_list);
		else
			current = next;
	}
}

void	merge_two(t_Token *current, t_Token *next, t_TokenType type)
{
	char	*merged_value;

	merged_value = NULL;
	if (!current || !next)
		return ;
	merged_value = malloc(ft_strlen(current->value) + \
	ft_strlen(next->value) + 1);
	if (!merged_value)
		exit(EXIT_FAILURE);
	ft_strlcpy(merged_value, current->value, (ft_strlen(current->value) + 1));
	ft_strlcat(merged_value, next->value, (ft_strlen(next->value) + \
	ft_strlen(current->value) + 1));
	free(current->value);
	current->value = merged_value;
	current->next = next->next;
	if (next->next)
		next->next->prev = current;
	current->type = type;
	current->length = ft_strlen(current->value);
	free(next->value);
	free(next);
}

void	merge_text_env_and_quote(t_Token **token_list)
{
	t_Token	*current;

	current = *token_list;
	while (current && current->next)
	{
		if ((current->type == T_S_QUOT || current->type == T_D_QUOT || \
		current->type == T_TEXT || current->type == T_ENV) \
		&& (current->next->type == T_S_QUOT || current->next->type == T_D_QUOT \
		|| current->next->type == T_TEXT || current->next->type == T_ENV))
		{
			merge_two(current, current->next, T_TEXT);
			continue ;
		}
		current = current->next;
	}
}
