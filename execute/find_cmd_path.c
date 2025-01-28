/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:42:52 by aroux             #+#    #+#             */
/*   Updated: 2025/01/28 17:30:48 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	dirty_little_secret(t_shell *data, char **env_tab, t_env **env);

/* parsing:
	we want to retrieve the envp[i]th element that starts with "PATH="
	(to find the paths were the commands are stored) 
	we then split these paths (jumping over the first 5 char, ie "PATH=")
	we split the command input by the user into command and arguments
	we concatenate all the paths with the input command to see if one 
	works (if it's executed by execve())
	we free what needs freeing, and we return the cmd_and_args to main */
int	find_cmd_path(t_shell *data, int i, t_env **env)
{
	char	**paths;
	char	*cmd_path;
	char	**cmd_and_args;
	char	**env_tab;

	env_tab = env_to_tab(data->env);
	paths = ft_split(get_path(env_tab), ':');
	if (!paths)
		dirty_little_secret(data, env_tab, env);
	cmd_and_args = data->cmds[i].cmd;
	cmd_path = find_valid_path(data->cmds[i].cmd[0], paths, data, env);
	if (!cmd_path)
	{
		free_many_splits(paths, env_tab);
		return (0);
	}
	if (data->cmds[i].path)
		free(data->cmds[i].path);
	data->cmds[i].path = cmd_path;
	data->cmds[i].cmd = cmd_and_args;
	free_many_splits(paths, env_tab);
	if (ft_strcmp(cmd_path, get_pwd_value("PWD", env)) == 0)
		return (0);
	return (1);
}

static void	dirty_little_secret(t_shell *data, char **env_tab, t_env **env)
{
	free_tab(env_tab);
	error_handle(data, "PATH not found", 0, env);
}

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*find_valid_path(char *cmd, char **paths, t_shell *data, t_env **my_env)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (paths[i])
	{
		cmd_path = multi_strjoin(paths[i], "/", cmd);
		if (!cmd_path)
			error_handle(data, "multi_strjoin failed", 0, my_env);
		if (access(cmd_path, R_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
				return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	return (NULL);
}
