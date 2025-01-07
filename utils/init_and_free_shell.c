/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free_shell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:50:26 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/07 17:23:36 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*init_shell_struct(t_env *env)
{
	t_shell	*data;

	data = malloc(sizeof(t_shell));
	if (!data)
		return (NULL);
	data->nb_cmds = 0;
	data->cmds = NULL;
	data->last_exit_status = 0;
	data->err_msg = NULL;
	data->env = env;
	data->std_in = dup(STDIN_FILENO);
	data->std_out = dup(STDOUT_FILENO);
	data->prev_fd = -2;
	return (data);
}

void	free_shell_struct_cmds(t_shell *data, int i)
{
	int	j;

	if (data->cmds[i].cmd)
	{
		j = 0;
		while (j < data->cmds[i].arg_count)
		{
			if (data->cmds[i].cmd[j])
			{
				free_nullify(data->cmds[i].cmd[j]);
				j++;
			}
		}
		free_nullify(data->cmds[i].cmd);
	}
	free_shell_struct_redir(data, i);
}

void	free_shell_struct_redir(t_shell *data, int i)
{
	int	j;

	if (data->cmds[i].redir)
	{
		j = 0;
		while (j < data->cmds[i].redirect_count)
		{
			if (data->cmds[i].redir[j].filename)
				free_nullify(data->cmds[i].redir[j].filename);
			j++;
		}
		free(data->cmds[i].redir);
		data->cmds[i].redir = NULL;
	}
}

void	free_shell_struct(t_shell *data, t_env **my_env)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i < data->nb_cmds)
	{
		if (data->cmds[i].path)
			free_nullify(data->cmds[i].path);
		if (data->cmds)
			free_shell_struct_cmds(data, i);
		i++;
	}
	if (data->err_msg)
		free_nullify(data->err_msg);
	close_fd(data->prev_fd);
	free_nullify(data->cmds);
	free_env_list(my_env, NULL, NULL);
	free(data);
}


void	clean_shell_struct(t_shell *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds)
	{
		if (data->cmds[i].path)
			free(data->cmds[i].path);
		free_shell_struct_cmds(data, i);
		i++;
	}
	if (data->err_msg)
		free(data->err_msg);
	free(data->cmds);
	data->cmds = NULL;
	data->err_msg = NULL;
	data->std_in = 0;
	data->std_out = 0;
	data->nb_cmds = 0;
	data->prev_fd = -2;
}
