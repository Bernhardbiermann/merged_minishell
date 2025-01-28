/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:13:34 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/28 12:20:23 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_name_and_empty_value(char *input)
{
	int	i;

	i = 0;
	if (ft_isalpha(input[0]) == 0 && input[0] != '_')
		return (1);
	while (input[i] != '=' && (ft_isalnum(input[i]) == 1 || input[i] == '_'))
		i++;
	if (input[i] != '=')
		return (1);
	else
		return (0);
}

int	is_valid_var_name(const char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (1);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

char	*safe_malloc(t_shell *data, size_t len)
{
	char	*value;

	value = malloc(len + 1);
	if (!value)
	{
		ft_printf("minishell: export: memory allocation error\n");
		data->last_exit_status = 1;
		return (NULL);
	}
	return (value);
}
