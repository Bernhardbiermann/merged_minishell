/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:24:01 by aroux             #+#    #+#             */
/*   Updated: 2025/01/09 15:54:31 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_handle(t_shell *data, char *err_msg, int err_no, t_env **my_env)
{
	perror(err_msg);
	//if (data && my_env)
	//	printf("hi\n");
	free_shell_struct(data, my_env);
	if (err_no == 0)
		exit(EXIT_FAILURE);
	else
		exit(err_no);
}

void	error_cmd_notfound(t_shell *data, int i, t_env **my_env)
{
	int	last_exit_status;

	//ft_printf("Command \'%s\' not found\n", data->cmds[i].cmd[0]);
	write(2, "Command \'", 10);
	write(2, data->cmds[i].cmd[0], ft_strlen( data->cmds[i].cmd[0]));
	write(2, "\' not found\n", 12);
	free_shell_struct(data, my_env);
	if (my_env)
		last_exit_status = 127;
	//free_env_list(my_env, NULL, NULL);
	last_exit_status = 127;
	exit(last_exit_status) ;
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