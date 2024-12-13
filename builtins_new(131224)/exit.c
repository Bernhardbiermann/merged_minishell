/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:21 by aroux             #+#    #+#             */
/*   Updated: 2024/12/13 14:43:17 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_a_number(char *str)
{
	int	i;

	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return 1;
		i++;
	}
	return (0);
}

void	ft_exit(char **args, t_shell *data)
{
	if (args[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}
	else if (!args[1])
	{
		printf("bye bye\n");
		exit (0);
	}
	else if (is_a_number(args[1]))
	{
		printf("bye bye with a special number\n");
		data->last_exit_status = atoi(args[1]);
		exit(atoi(args[1]));
	}
	else
	{
		ft_printf("exit: %s: numeric argument required\n", args[1]);
		data->last_exit_status = 255;
		exit(255);//131224 B: ..or exit-status 2..
	}
}
