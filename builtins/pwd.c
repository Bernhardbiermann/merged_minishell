/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:29:51 by aroux             #+#    #+#             */
/*   Updated: 2025/01/24 15:55:46 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_pwd_value(char *envp_key, t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, envp_key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	ft_pwd(t_shell *data, t_env **env)
{
	char	*cwd;

	cwd = get_pwd_value("PWD", env);
	if (cwd == NULL)
		return (1);
	printf("%s\n", cwd);
	data->last_exit_status = 0;
	return (0);
}
