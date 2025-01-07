/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:21 by aroux             #+#    #+#             */
/*   Updated: 2025/01/07 11:36:04 by bbierman         ###   ########.fr       */
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
	
	if (!args[1])
	{
		printf("bye bye\n");
		exit_status = 0;
	}
	else if (args[1] && args[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		exit_status = 1;
	}

	else if (is_a_number(args[1]) == 0)
	{
		printf("bye bye with a special number\n");
		exit_status = atoi(args[1]);
	}
	else
	{
		ft_printf("exit: %s: numeric argument required\n", args[1]);
		exit_status = 255;
	}
	free_shell_struct(data, my_env);
	exit(exit_status);
}
