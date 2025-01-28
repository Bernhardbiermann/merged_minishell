/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:21 by aroux             #+#    #+#             */
/*   Updated: 2025/01/28 11:35:47 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_a_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(char **args, t_shell *data, t_env **my_env)
{
	int	exit_status;

	if (args[1] && args[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		exit_status = 1;
	}
	else if (args[1] && ft_atoi(args[1]) != 0)
	{
		if (ft_atoi(args[1]) > 0)
			exit_status = ft_atoi(args[1]) % 256;
		else
			exit_status = (256 + ft_atoi(args[1])) % 256;
	}
	else if (args[1] && !ft_isdigit(args[1][0]))
	{
		ft_printf("minishell: exit: numeric argument required\n");
		exit_status = 2;
	}
	else
		exit_status = 0;
	free_shell_struct(data, my_env);
	ft_printf("exit\n");
	exit(exit_status);
}
