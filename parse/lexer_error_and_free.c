/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error_and_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:39:21 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/15 10:50:14 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token_list(t_Token *token_list)
{
	t_Token	*temp;

	while (token_list)
	{
		temp = token_list;
		token_list = token_list->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}

void	free_hdoc_token_list(t_hdoc *token_list)
{
	t_hdoc	*temp;

	while (token_list)
	{
		temp = token_list;
		token_list = token_list->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}

void	three_frees(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
}