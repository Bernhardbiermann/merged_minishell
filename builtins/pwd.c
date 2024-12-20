/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:29:51 by aroux             #+#    #+#             */
/*   Updated: 2024/12/20 10:53:44 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_shell *data) //201224 B: Don't know how to safe the exitstatus..
{
	char	*cwd;

	cwd = malloc(1024);
	if (!cwd)
	{
		perror("malloc");
		data->last_exit_status = 1;
		return (1);
	}
	cwd = getcwd(cwd, 1024);
	if (!cwd)
	{
		perror("pwd");
		free(cwd);
		data->last_exit_status = 1;
		return (1);
	}
	printf("%s\n", cwd); //201224 B: changed ft_put_str --> printf
	free(cwd);
	data->last_exit_status = 0;
	return (0);
}
