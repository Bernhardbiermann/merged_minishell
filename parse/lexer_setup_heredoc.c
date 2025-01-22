/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_setup_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:09:44 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/22 13:50:57 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_heredoc_token(t_shell *data, t_Token **token_list, t_env **env)
{
	t_Token	*current;

	if (!data || !env)
		return ;
	current = *token_list;
	while (current && current->grammer_err == 0)
	{
		if (current->type == T_HEREDOC)
		{
			current->hdoc_delim = ft_strdup(current->next->value);
			exec_heredoc(data, current, current->next->value, env);
		}
		current = current->next;
	}
}
