/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:13:34 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/08 17:18:05 by bbierman         ###   ########.fr       */
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
	i++;
	if (input[i] == '\0')
		return (1);
	else
		return (0);
}
