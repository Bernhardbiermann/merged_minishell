/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_t_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:31:07 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/24 11:56:30 by aroux            ###   ########.fr       */
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
