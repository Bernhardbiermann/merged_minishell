/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:16 by aroux             #+#    #+#             */
/*   Updated: 2025/01/28 10:51:53 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_shell *data, t_cmd *cmd, t_env **env)
{
	if (cmd->arg_count > 1)
	{
		write(2, "env: too many arguments\n", 24);
		data->last_exit_status = 1;
	}
	else
		print_env(*env);
}
