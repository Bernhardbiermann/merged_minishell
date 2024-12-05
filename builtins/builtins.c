/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:45:41 by aroux             #+#    #+#             */
/*   Updated: 2024/12/05 14:24:30 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_shell *data, int i)
{
	if (ft_strcmp(data->cmds[i]->cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(data->cmds[i]->cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(data->cmds[i]->cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(data->cmds[i]->cmd[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(data->cmds[i]->cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(data->cmds[i]->cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(data->cmds[i]->cmd[0], "unset") == 0)
		return (1);
	else
		return (0);
}

/* void	builtin_functions(t_shell *data, int i) // probably what i'm gonna pass is actually a struct
{
	if (ft_strcmp(data->cmds[i]->cmd_name, "cd") == 0)
		ft_cd(data->cmds[i]->cmd[i][2]);
	else if (ft_strcmp(data->cmds[i]->cmd_name, "echo") == 0)
		ft_echo(*str, arg); // so this is probably gonna be part of the struct
	else if (ft_strcmp(data->cmds[i]->cmd_name, "env") == 0) // this is pseudocode, do it with stringcompare or with an enum struct
		list_envp_vars(envp);
	else if (ft_strcmp(data->cmds[i]->cmd_name, "exit") == 0)
		// trigger exit function
	else if (ft_strcmp(data->cmds[i]->cmd_name, "export") == 0)
		// trigger export function
	else if (ft_strcmp(data->cmds[i]->cmd_name, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(data->cmds[i]->cmd_name, "unset") == 0)
		//trigger unset function 
}*/


// function that checks if builtin or external fonction

// if function is external, check path and just execute the function