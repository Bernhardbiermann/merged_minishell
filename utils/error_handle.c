/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:24:01 by aroux             #+#    #+#             */
/*   Updated: 2025/01/28 16:18:02 by aroux            ###   ########.fr       */
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

	cmd_name = data->cmds[i].cmd[0];
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
	char	*trim;
	int		exit_status;

	trim = ft_strtrim(cmd_name, ".");
	dir = opendir(trim);
	write(2, cmd_name, ft_strlen(cmd_name));
	if (dir)
	{
		write(2, ": Is a directory\n", ft_strlen(": Is a directory\n"));
		exit_status = 126;
		closedir(dir);
	}
	else if (access(cmd_name, F_OK) >= 0 && access(cmd_name, X_OK) == -1)
	{
		write(2, ": Permission denied\n", ft_strlen(": Permission denied\n"));
		exit_status = 126;
	}
	else
	{
		write(2, ": No such file or directory\n", 28);
		exit_status = 127;
	}
	free(trim);
	free_shell_exit(data, env, exit_status);
}

void	free_shell_exit(t_shell *data, t_env **env, int errno)
{
	free_shell_struct(data, env);
	exit(errno);
}
