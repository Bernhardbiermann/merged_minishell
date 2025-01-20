/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mark_last_infile.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:05:59 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/20 14:33:36 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		mark_last_in_or_heredoc(t_shell *data, int j)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < data->cmds[j].redirect_count)
	{
		if (data->cmds[j].redir[i].type == T_HEREDOC || \
		data->cmds[j].redir[i].type == T_INPUT)
			count = i;
		i++;
	}
	if (count != 0)
		data->cmds[j].redir[count].last_redir_in = 1;
}

void	mark_last_infile(t_shell *data)
{
	int	i;

	i = 0;
	if (data->nb_cmds < 1)
		return ;
	while (i < data->nb_cmds)
	{
		mark_last_in_or_heredoc(data, i);
		i++;
	}
}
