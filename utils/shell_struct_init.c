/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_struct_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:25:11 by aroux             #+#    #+#             */
/*   Updated: 2025/01/14 16:33:38 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*init_shell_struct(t_env *env)
{
	t_shell	*data;

	data = malloc(sizeof(t_shell));
	if (!data)
		return (NULL);
	data->pids = NULL;
	data->nb_cmds = 0;
	data->cmds = NULL;
	data->hdoc = NULL;
	data->last_exit_status = 0;
	data->err_msg = NULL;
	data->env = env;
	data->prev_fd = -2;
	return (data);
}

