/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_lexer_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:30:30 by bbierman          #+#    #+#             */
/*   Updated: 2024/11/27 13:25:42 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

Token	*delete_node_and_glue(Token *target, Token **token_list)
{
	Token	*temp;
	
	temp = NULL;
	if (!target || !token_list || !*token_list)
		return (NULL);
	if (target->prev == NULL)
	{
		*token_list = target->next;
		if(target->next)
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

void	delete_empty_ENV_and_quote(Token **token_list)
{
	Token	*current;
	Token	*next;
	
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
void	delete_spaces(Token **token_list)
{
	Token	*current;
	Token	*next;
	
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

void	merge_two(Token *current, Token *next)
{
	char	*merged_value;

	if (!current || !next)
		return ;
	if (!(merged_value = malloc(ft_strlen(current->value) + \
	ft_strlen(next->value) + 1)))
		exit(EXIT_FAILURE);
	ft_strlcpy(merged_value, current->value, (ft_strlen(current->value) + 1));
	ft_strlcat(merged_value, next->value, (ft_strlen(next->value)+ \
	ft_strlen(current->value) + 1));
	free(current->value);
	current->value = merged_value;
	current->next = next->next;
	if (next->next)
		next->next->prev = current;
	current->type = T_TEXT;
	current->length = ft_strlen(current->value);
	free(next->value);
	free(next);
}

void	merge_text_env_and_quot(Token **token_list)
{
	Token	*current;
	
	current = *token_list;
	while (current && current->next)
	{
		if((current->type == T_S_QUOT || current->type == T_D_QUOT || \
		current->type == T_TEXT || current->type == T_ENV) \
		&& (current->next->type == T_S_QUOT || current->next->type == T_D_QUOT \
		|| current->next->type == T_TEXT || current->type == T_ENV))
			merge_two(current, current->next);
		else
			current = current->next;
	}
}
