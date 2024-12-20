/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:45:41 by aroux             #+#    #+#             */
/*   Updated: 2024/12/20 10:54:12 by bbierman         ###   ########.fr       */
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

void	exec_builtin(t_shell *data, int i)
{
	if (ft_strcmp(data->cmds[i].cmd[0], "cd") == 0)
		ft_cd(data, data->cmds[i].cmd[1]);		// 18.12 A: seems to work fine 
	else if (ft_strcmp(data->cmds[i].cmd[0], "echo") == 0)
		ft_echo(data->cmds[i].cmd);				// 18.12 A: echo segfaults
	else if (ft_strcmp(data->cmds[i].cmd[0], "env") == 0)
		print_env(data->env);					// 18.12 A: is print_env() any different from what's currently defined in env.c?
	else if (ft_strcmp(data->cmds[i].cmd[0], "exit") == 0)
		ft_exit(data->cmds[i].cmd, data);		// 18.12 A: I think it works but not sure of expected funct behaviour
	else if (ft_strcmp(data->cmds[i].cmd[0], "export") == 0)
		ft_export(data->cmds[i].cmd, data);		// 18.12 A: export has a weird behaviour, also printing werid characters
	else if (ft_strcmp(data->cmds[i].cmd[0], "pwd") == 0)
		ft_pwd(data);								// 18.12 A: seems to work fine 
	else if (ft_strcmp(data->cmds[i].cmd[0], "unset") == 0)
		ft_unset(data, data->cmds[i].cmd);		// 18.12 A: didn't erase the vars created yesterday (VAR123), only the ones created today, for some reason
	return ;
}

/* 18.12 A: old version of the exec_builtin function, might not be of use
void	builtin_functions(t_shell *data, int i) // probably what i'm gonna pass is actually a struct
{
	if (ft_strcmp(data->cmds[i]->cmd_name, "cd") == 0)
		ft_cd(data->cmds[i]->cmd[i][2]);
	else if (ft_strcmp(data->cmds[i]->cmd_name, "echo") == 0)
		ft_echo(*str, arg); // so this is probably gonna be part of the struct
	else if (ft_strcmp(data->cmds[i]->cmd_name, "env") == 0) // this is pseudocode, do it with stringcompare or with an enum struct
		print_env(data->env); // 18.12 A: is print_env() any different from what's currently defined in env.c?
	else if (ft_strcmp(data->cmds[i]->cmd_name, "exit") == 0)
		ft_exit(data->cmds[i].cmd, data);
	else if (ft_strcmp(data->cmds[i]->cmd_name, "export") == 0)
		ft_export(data->cmds[i].cmd, data);
	else if (ft_strcmp(data->cmds[i]->cmd_name, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(data->cmds[i]->cmd_name, "unset") == 0)
		ft_unset(data, data->cmds[i].cmd);
}
*/


// function that checks if builtin or external fonction

// if function is external, check path and just execute the function