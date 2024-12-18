/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:48:43 by aroux             #+#    #+#             */
/*   Updated: 2024/12/18 14:23:16 by aroux            ###   ########.fr       */
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
		return 1;
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return 1;
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
	while (check_for_option_n(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1] != NULL)
			write (1, " ", 1);
		i++;
	}
	if (newline != 0)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
