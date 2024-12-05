/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_and_free.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bernhardbiermann <bernhardbiermann@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 11:24:32 by bernhardbie       #+#    #+#             */
/*   Updated: 2024/12/01 12:46:33 by bernhardbie      ###   ########.fr       */
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
			free(data->cmds[i].arg);
			free(data->cmds[i].redirect);
			i++;
		}
		free(data->cmds);
	}
}

void	*safe_malloc_shell(size_t size, t_shell *data)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		free_shell(data);
		exit (1);
	}
	return (ptr);
}
