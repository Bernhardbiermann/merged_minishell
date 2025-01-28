/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:24:01 by aroux             #+#    #+#             */
/*   Updated: 2025/01/28 10:21:37 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_handle(t_shell *data, char *err_msg, int err_no, t_env **my_env)
{
	perror(err_msg);
	free_shell_struct(data, my_env);
	if (err_no == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	else
		exit(err_no);
}

void	error_cmd_file_dir(t_shell *data, int i, t_env **env)
{
	char	*cmd_name;
	//char	*cwd;

	cmd_name = data->cmds[i].cmd[0];
/* 	if ((cmd_name[0] == '.' && cmd_name[1] == '/') || cmd_name[0] == '/')
	{
		if ((cmd_name[0] == '.' && cmd_name[1] == '/'))
		{
			cwd = get_pwd_value("PWD", env);
			if (execve(cwd, cmd_name, env_to_tab(data->env)) == -1)
				continue ;
		}
		error_directory(data, cmd_name, env);
	} */
 	if ((cmd_name[0] == '.' && cmd_name[1] == '/') || cmd_name[0] == '/')
		error_directory(data, cmd_name, env);
	else
	{
		if (access(cmd_name, F_OK) >= 0 && access(cmd_name, R_OK) == -1)
		{
			write(2, cmd_name, ft_strlen(cmd_name));
			write(2, ": Permission denied\n", ft_strlen(": Permission denied\n"));
			free_shell_exit(data, env, 126);
		}
		write(2, "Command \'", 10);
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, "\' not found\n", 12);
		free_shell_exit(data, env, 127);
	}
}

void	error_directory(t_shell *data, char *cmd_name, t_env **env)
{
	DIR		*dir;

	if (access(cmd_name, F_OK) >= 0 && access(cmd_name, X_OK) == -1)
	{
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": Permission denied\n", ft_strlen(": Permission denied\n"));
		free_shell_exit(data, env, 126);
	}
	dir = opendir(ft_strtrim(cmd_name, "./"));
	if (dir)
	{
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": Is a directory\n", ft_strlen(": Is a directory\n"));
		closedir(dir);
		free_shell_exit(data, env, 126);
	}
	else
	{
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": No such file or directory\n", 28);
		closedir(dir);
		free_shell_exit(data, env, 127);
	}
}

void	free_shell_exit(t_shell *data, t_env **env, int errno)
{
	free_shell_struct(data, env);
	exit(errno);
}
