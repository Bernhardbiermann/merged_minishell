/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free_shell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:50:26 by bbierman          #+#    #+#             */
/*   Updated: 2024/12/12 10:08:35 by bbierman         ###   ########.fr       */
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
				free(data->cmds[i].cmd[j]);
				j++;
			}
		}
		free(data->cmds[i].cmd);	
	}
}

void	free_shell_struct_redir(t_shell *data, int i)
{
	int	j;

	if (data->cmds[i].redir)
	{
		j = 0;
		while (j < data->cmds[i].redirect_count)
		{
			if (data->cmds[i].redir[j].infile)
				free(data->cmds[i].redir[j].infile);
			if (data->cmds[i].redir[j].trunc)
				free(data->cmds[i].redir[j].trunc);
			if (data->cmds[i].redir[j].append)
				free(data->cmds[i].redir[j].append);
			if (data->cmds[i].redir[j].here_delim)
				free(data->cmds[i].redir[j].here_delim);
			j++;
		}
		free(data->cmds[i].redir);
	}
}

void	free_shell_struct(t_shell *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds)
	{
		if (data->cmds[i].path)
			free(data->cmds[i].path);
		free_shell_struct_cmds(data, i);
		free_shell_struct_redir(data, i);
		i++;
	}
	if (data->err_msg)
		free(data->err_msg);
	free(data->cmds);
	free(data);
}

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
	return (data);
}