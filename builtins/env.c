/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:16 by aroux             #+#    #+#             */
/*   Updated: 2024/12/13 14:24:07 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	list_envp_vars(char **envp)
{
	if (!envp)
	{
		printf("No enviromental variables available.\n");
		return ;
	}
	while (**envp)
	{
		ft_printf("%s\n", *envp);
		envp++;
	}
}
