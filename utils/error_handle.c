/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:24:01 by aroux             #+#    #+#             */
/*   Updated: 2025/01/16 13:44:23 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_handle(t_shell *data, char *err_msg, int err_no, t_env **my_env)
{
	perror(err_msg);
	//if (data && my_env)
	//	printf("hi\n");
	free_shell_struct(data, my_env);
	if (err_no == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	else
		exit(err_no);
}

void	error_cmd_notfound(t_shell *data, int i, t_env **my_env)
{
	DIR		*dir;
	char	*cmd_name;

	cmd_name = data->cmds[i].cmd[0];
	dir = opendir(cmd_name);
	if (dir)
	{
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": Is a directory\n", ft_strlen(": Is a directory\n"));
		closedir(dir);
		free_shell_struct(data, my_env);
		exit(126);
	}
	else
	{
		write(2, "Command \'", 10);
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, "\' not found\n", 12);
		free_shell_struct(data, my_env);
		exit(127);
	}
}

void	close_fd(int fd)
{
	if (fd >= 0)
		close(fd);
	else
		return ;
}

/* void	error_handle(char *error_msg, int err_code)
{
	perror(error_msg);
	if (err_code == 0)
		exit(EXIT_FAILURE);
	else
		exit(err_code);
} */