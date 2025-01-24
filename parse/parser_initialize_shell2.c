/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initialize_shell2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:13:15 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/24 12:20:27 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_redir(t_redir *current, int redirect_count)
{
	int	i;

	if (!current || redirect_count <= 0)
		return ;
	i = 0;
	while (i < redirect_count)
	{
		current->type = T_ERROR;
		current->filename = NULL;
		current->last_redir_in = 0;
		current++;
		i++;
	}
}

void	initialize_cmds(int cmd_c, t_shell *data)
{
	int	i;

	if (!data || !data->cmds || cmd_c < 0 || cmd_c >= data->nb_cmds)
		return ;
	if (!data->cmds[cmd_c].cmd)
		return ;
	i = 0;
	while (i < (data->cmds[cmd_c].arg_count + 1))
	{
		data->cmds[cmd_c].cmd[i] = NULL;
		i++;
	}
}
