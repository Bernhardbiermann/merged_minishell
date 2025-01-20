/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:23:09 by aroux             #+#    #+#             */
/*   Updated: 2025/01/17 15:26:16 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	collect_status_free_exit(t_shell *data, t_env **env)
{
	int		exit_status;

	exit_status = data->last_exit_status;
	free_shell_struct(data, env);
	exit(exit_status);
}

void	close_fd(int fd)
{
	if (fd >= 0)
		close(fd);
	else
		return ;
}

void	multi_close(int fds[], int size, int infile, int outfile)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close_fd(fds[i]);
		i++;
	}
	close_fd(infile);
	close_fd(outfile);
	return ;
}
