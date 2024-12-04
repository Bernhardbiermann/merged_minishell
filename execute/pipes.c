/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:25:33 by aroux             #+#    #+#             */
/*   Updated: 2024/12/02 10:14:07 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_pipes(t_shell *data, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		data->pipes[i] = malloc(sizeof(int) * 2);
		if (!data->pipes[i])
		{
			close_pipes(data, i - 1, i);
			error_handle("Malloc for pipes failed", 0);
		}
		if (pipe(data->pipes[i]) < 0)
		{
			close_pipes(data, i - 1, i);
			error_handle("Pipe creation failed", 0);
		}
		i++;
	}
}

void	close_pipes(t_shell *data, int nb_pipes, int index_process)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if (data->pipes[i] && i != index_process)
		{
			close(data->pipes[i][0]);
			close(data->pipes[i][1]);
			free(data->pipes[i]);
		}
		i++;
	}
	free(data->pipes);
}
