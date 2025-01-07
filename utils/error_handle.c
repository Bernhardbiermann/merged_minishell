/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:24:01 by aroux             #+#    #+#             */
/*   Updated: 2025/01/07 17:58:55 by aroux            ###   ########.fr       */
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