/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:08 by aroux             #+#    #+#             */
/*   Updated: 2025/01/28 13:43:25 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* change directory to the specified path
	if no path is provided, it should switch to the user's home directory 
	chdir already interprets .. and . properly */
/* also update your oldpwd (see export): 
"If, during the execution of the above steps, the PWD environment  variable 
	is  set, the OLDPWD environment variable shall also be set to the value 
	of the old working directory (that is the current working  directory 
	immediately prior to the call to cd)." */
static void	set_errorstatus_and_print_msg(t_shell *data, char *input)
{
	data->last_exit_status = 1;
	ft_printf(input);
}

void	update_pwd(char *envp_key, char *envp_new_value, t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, envp_key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(envp_new_value);
			return ;
		}
		current = current->next;
	}
}

static int	is_dir_check(t_shell *data, int i)
{
	DIR		*dir;

	dir = opendir(data->cmds[i].cmd[1]);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	else if (!dir)
	{
		write(2, data->cmds[i].cmd[1], ft_strlen(data->cmds[i].cmd[1]));
		write(2, ": No such file or directory\n", 28);
		data->last_exit_status = 1;
		return (0);
	}
	return (1);
}

void	ft_cd(t_shell *data, char *path, int i, t_env **env)
{
	char	*new_value;

	if (data->cmds[i].cmd[1] && is_dir_check(data, i) == 0)
		return ;
	if (data->cmds[i].arg_count > 2)
	{
		set_errorstatus_and_print_msg(data, "cd: too many arguments\n");
		return ;
	}
	update_pwd("OLDPWD", get_pwd_value("PWD", env), env);
	if (!path)
	{
		path = get_pwd_value("HOME", env);
		if (!path)
			return (perror("No home directory set"));
	}
	if (chdir(path) == -1)
	{
		set_errorstatus_and_print_msg(data, "cd: No such file or directory\n");
		return ;
	}
	new_value = getcwd(NULL, 0);
	update_pwd("PWD", new_value, env);
	free(new_value);
	data->last_exit_status = 0;
	return ;
}
