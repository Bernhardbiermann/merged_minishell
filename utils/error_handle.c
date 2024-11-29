/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:24:01 by aroux             #+#    #+#             */
/*   Updated: 2024/11/26 16:38:30 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_handle(char *error_msg, int err_code)
{
	perror(error_msg);
	if (err_code == 0)
		exit(EXIT_FAILURE);
	else
		exit(err_code);
}

/* void	error_handle(char *error_msg, int err_code)
{
	perror(error_msg);
	if (err_code == 0)
		exit(EXIT_FAILURE);
	else
		exit(err_code);
} */