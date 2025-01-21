/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_struct_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:25:11 by aroux             #+#    #+#             */
/*   Updated: 2025/01/20 17:15:19 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*init_shell_struct(t_env *env)
{
	t_shell	*data;

	setup_signal(INTERACTIVE);
	data = malloc(sizeof(t_shell));
	if (!data)
		return (NULL);
	data->pids = NULL;
	data->nb_cmds = 0;
	data->cmds = NULL;
	data->hdoc = NULL;
	data->fd_heredoc = -1;
	data->last_exit_status = 0;
	data->err_msg = NULL;
	data->env = env;
	data->prev_fd = -2;
	return (data);
}

