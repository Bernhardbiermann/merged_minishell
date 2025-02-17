/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:45:41 by aroux             #+#    #+#             */
/*   Updated: 2025/01/28 10:50:13 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_shell *data, int i)
{
	if (ft_strcmp(data->cmds[i].cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(data->cmds[i].cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(data->cmds[i].cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(data->cmds[i].cmd[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(data->cmds[i].cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(data->cmds[i].cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(data->cmds[i].cmd[0], "unset") == 0)
		return (1);
	else
		return (0);
}

void	exec_builtin(t_shell *data, int i, t_env **my_env)
{
	if (ft_strcmp(data->cmds[i].cmd[0], "cd") == 0)
		ft_cd(data, data->cmds[i].cmd[1], i, my_env);
	else if (ft_strcmp(data->cmds[i].cmd[0], "echo") == 0)
		ft_echo(data->cmds[i].cmd);
	else if (ft_strcmp(data->cmds[i].cmd[0], "env") == 0)
		ft_env(data, &data->cmds[i], my_env);
	else if (ft_strcmp(data->cmds[i].cmd[0], "exit") == 0)
		ft_exit(data->cmds[i].cmd, data, my_env);
	else if (ft_strcmp(data->cmds[i].cmd[0], "export") == 0)
		ft_export(data->cmds[i].cmd, data);
	else if (ft_strcmp(data->cmds[i].cmd[0], "pwd") == 0)
		ft_pwd(data, my_env);
	else if (ft_strcmp(data->cmds[i].cmd[0], "unset") == 0)
		ft_unset(data, data->cmds[i].cmd);
	return ;
}
