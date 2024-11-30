/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:58:28 by bbierman          #+#    #+#             */
/*   Updated: 2024/11/30 15:43:50 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_cmds(t_shell *data, Token **token_list)
{
	Token	*current;
	Token	*next;
	t_cmd	*current_cmd;

	current = *token_list;
	next = NULL;
	current_cmd = data->cmds;
	while (current)
	{
		next = current->next;
		if (current->type == T_ERROR)
		{
			data->last_exit_status = current->length;
			data->err_msg = ft_strdup(current->value);
			return ;
		}
		else if (current->type == T_TEXT)
		{
			data
		}
		else if ((current->type == T_INPUT || current->type == T_OUTPUT || \
		current->type == T_APPEND || current->type == T_HEREDOC) && \
		next->type == T_TEXT)
		{
			data
		}
	}
	
}

void	parse_to_shell(t_shell*	data, Token **token_list)
{
	data->nb_cmds = count_cmds(token_list);
	if (!(data->cmds = malloc(sizeof(t_cmd) * data->nb_cmds + 1))
		exit (1);
	
}