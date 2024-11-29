/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:48:43 by aroux             #+#    #+#             */
/*   Updated: 2024/11/12 11:57:20 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Clarify if check needed that the var exists before using getenv. 
If that's the case use function below (expand_var)*/
int	ft_echo(char *str, char arg)
{
	int		i;
	int		start;
	char	*var_name;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i;
			while (str[i] && str[i] != ' ')
				i++;
			var_name = malloc((i - start + 1) * sizeof(char));
			if (!var_name)
				return (EXIT_FAILURE);
			ft_strncpy(var_name, str + start, i - start); 
			ft_printf("%s", get_env(var_name));
			free(var_name);
		}
		else
			write(1, &str[i++], 1);
	}
	if (arg != 'n')
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

/* void	expand_var(char *var_name)
{
	char	*var_val;

	if (getenv(var_name))
		var_val = getenv(var_name);
	ft_printf("%s", var_val);
} */