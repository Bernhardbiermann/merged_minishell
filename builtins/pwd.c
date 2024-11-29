/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:29:51 by aroux             #+#    #+#             */
/*   Updated: 2024/11/11 16:43:20 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (-1);
	}
	ft_putstr_fd(cwd, 1);
	free(cwd);
	return (0);
}