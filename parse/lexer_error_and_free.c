/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error_and_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:39:21 by bbierman          #+#    #+#             */
/*   Updated: 2024/11/26 14:32:52 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token_list(Token *token_list)
{
	Token	*temp;

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