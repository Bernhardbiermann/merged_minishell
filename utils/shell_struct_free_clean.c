/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_struct_free_clean.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:50:26 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/16 13:59:11 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	free_pids_struct(t_pids **pids)
{
	t_pids	*current;
	t_pids	*next;

	if (!pids || !*pids)
		return ;
	current = *pids;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*pids = NULL;
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
	if (data->hdoc)
		free_hdoc_token_list(data->hdoc);
	close_fd(data->prev_fd);
	free_pids_struct(&data->pids);
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
	if (data->hdoc)
	{
		free_hdoc_token_list(data->hdoc);
		data->hdoc = NULL;
	}
	free_pids_struct(&data->pids);
	free(data->cmds);
	data->cmds = NULL; // should it be here free_nullify()?
	data->err_msg = NULL;
	data->std_in = 0;
	data->std_out = 0;
	data->nb_cmds = 0;
	data->prev_fd = -2;
}

