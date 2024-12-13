/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:48:43 by aroux             #+#    #+#             */
/*   Updated: 2024/12/13 11:42:53 by bbierman         ###   ########.fr       */
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
	int		j;
	int		new_line;

	i = 1;
	new_line = 0;
	while (check_for_option_n(args[i]))
	{
		new_line = 1;
		i++;
	}
	while (args[i])
	{
		while (args[i][j])
			write(1, &args[i][j++], 1);
		if (args[i + 1] != NULL)
			write (1, " ", 1);
		i++;
	}
	if (new_line != 0)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
