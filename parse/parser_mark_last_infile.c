/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_mark_last_infile.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:05:59 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/20 15:28:16 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		mark_last_in_or_heredoc(t_shell *data, int i)
{
	int	j;
	int	count;

	count = -1;
	j = 0;
	while (j < data->cmds[i].redirect_count)
	{
		if (data->cmds[i].redir[j].type == T_HEREDOC || \
		data->cmds[i].redir[j].type == T_INPUT)
			count = j;
		j++;
	}
	if (count != -1)
		data->cmds[i].redir[count].last_redir_in = 1;
}

void	mark_last_infile(t_shell *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds)
	{
		mark_last_in_or_heredoc(data, i);
		i++;
	}
}
