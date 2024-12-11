/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_lexer_token2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:54:25 by bbierman          #+#    #+#             */
/*   Updated: 2024/12/11 12:34:24 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_empty_DQUOT(t_Token **token_list)
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

void	make_text_out_of_quot(t_Token **token_list)
{
	t_Token	*current;

	current = *token_list;
	while (current)
	{
		if ((current->type == T_D_QUOT) || (current->type == T_S_QUOT))
			current->type = T_TEXT;
		current = current->next;
	}
}
