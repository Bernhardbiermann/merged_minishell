/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_and_free.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 11:24:32 by bernhardbie       #+#    #+#             */
/*   Updated: 2024/12/20 14:42:22 by aroux            ###   ########.fr       */
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

t_redirect	*safe_malloc_redir(size_t size, t_shell *data)
{
	t_redirect	*ptr;

	ptr = malloc(sizeof(t_redirect) * size);
	if (!ptr)
	{
		free_shell(data);
		//data->last_exit_status = 1;
		exit (1);
	}
	return (ptr);
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
