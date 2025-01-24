/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_lexer_token2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:54:25 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/24 12:16:57 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_empty_dquot(t_Token **token_list)
{
	t_Token	*current;

	current = *token_list;
	while (current)
	{
		if (current->prev && current->next)
		{
			if (current->next->type == T_SPACE && \
			current->prev->type == T_SPACE && (current->type == T_D_QUOT || \
			current->type == T_S_QUOT) && current->value[0] == '\0')
			{
				if (current->value)
					free(current->value);
				current->value = ft_strdup(" ");
				current->length = ft_strlen(current->value);
				current->type = T_TEXT;
			}
		}
		current = current->next;
	}
}

void	make_text_out_of_quot_and_env(t_Token **token_list)
{
	t_Token	*current;

	current = *token_list;
	while (current)
	{
		if ((current->type == T_D_QUOT) || (current->type == T_S_QUOT) || \
		(current->type == T_ENV))
			current->type = T_TEXT;
		current = current->next;
	}
}
