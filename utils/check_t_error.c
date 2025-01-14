/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_t_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:31:07 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/09 16:41:17 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_t_error(t_shell *data)
{
	if (!data->err_msg)
		return (0);
	else
	{
		ft_printf(data->err_msg);
		ft_printf("\n");
		return (1);
	}
}