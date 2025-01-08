/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:48:43 by aroux             #+#    #+#             */
/*   Updated: 2025/01/08 16:48:36 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Clarify if check needed that the var exists before using getenv. 
If that's the case use function below (expand_var)*/

int	check_for_option_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] != '-')
		return (1);
	i++;
	if (arg[1] != 'n')
		return (1);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(char **args)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	if (!args || !*args)
		return (1);
	while (args[i] && check_for_option_n(args[i]) == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline == 1)
		printf("\n");
	return (EXIT_SUCCESS);
}
