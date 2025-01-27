/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_struct_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:25:11 by aroux             #+#    #+#             */
/*   Updated: 2025/01/27 12:19:22 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*init_shell_struct(t_env *env)
{
	t_shell	*data;

	setup_signal(INTERACTIVE);
	data = malloc(sizeof(t_shell));
	if (!data)
	{
		printf("Failed to initialize shell struct.\n");
		return (NULL);
	}
	data->pids = NULL;
	data->nb_cmds = 0;
	data->cmds = NULL;
	data->token_list = NULL;
	data->fd_heredoc = -1;
	data->last_exit_status = 0;
	data->err_msg = NULL;
	data->env = env;
	data->prev_fd = -2;
	data->sigint_hdoc = 0;
	return (data);
}
