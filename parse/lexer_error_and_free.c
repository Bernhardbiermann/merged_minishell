/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error_and_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:39:21 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/27 15:28:49 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token_list(t_Token *token_list)
{
	t_Token	*tmp;
	t_Token	*next;

	if (!token_list)
		return ;
	tmp = token_list;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->value)
			free(tmp->value);
		if (tmp->hdoc_delim)
			free(tmp->hdoc_delim);
		if (tmp->hdoc_name)
			free(tmp->hdoc_name);
		free(tmp);
		tmp = next;
	}
	token_list = NULL;
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
