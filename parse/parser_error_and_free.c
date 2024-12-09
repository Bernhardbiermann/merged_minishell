/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_and_free.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 11:24:32 by bernhardbie       #+#    #+#             */
/*   Updated: 2024/12/09 17:45:40 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_shell(t_shell *data)
{
	int	i;

	i = 0;
	if (data->cmds)
	{
		while (i < data->nb_cmds)
		{
			free(data->cmds[i].cmd);
			free(data->cmds[i].redir);
			i++;
		}
		free(data->cmds);
	}
}

void	*safe_malloc_shell(size_t size, t_shell *data)
{
	void	*ptr;

	ptr = calloc(1, size);
	if (!ptr)
	{
		free_shell(data);
		exit (1);
	}
	return (ptr);
}
