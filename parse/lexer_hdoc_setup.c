/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_hdoc_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:09:44 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/28 12:17:35 by aroux            ###   ########.fr       */
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
		if (current->type == T_HEREDOC && data->sigint_hdoc == 0)
		{
			current->hdoc_delim = ft_strdup(current->next->value);
			data->last_exit_status = exec_heredoc(data, current, \
			current->next->value, env);
			if (data->last_exit_status == 130)
			{
				data->sigint_hdoc = 1;
				unlink(current->hdoc_name);
				break ;
			}
			if (check_t_error(token_list) != 0)
				unlink(current->hdoc_name);
		}
		current = current->next;
	}
}
