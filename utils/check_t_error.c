/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_t_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:31:07 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/27 14:09:32 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_t_error(t_Token **token_list)
{
	t_Token	*current;

	current = *token_list;
	while (current)
	{
		if (current->grammer_err != 0)
			return (1);
		current = current->next;
	}
	return (0);
}
