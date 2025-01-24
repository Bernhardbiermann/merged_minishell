/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:17:27 by aroux             #+#    #+#             */
/*   Updated: 2025/01/24 11:57:28 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_size(t_env *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

/* converts environment list to an array of strings, to use it in execve() */
char	**env_to_tab(t_env *env)
{
	char	**tab;
	int		i;
	int		size;

	size = env_size(env);
	tab = malloc((size + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (env)
	{
		tab[i] = multi_strjoin(env->key, "=", env->value);
		if (!tab[i])
		{
			while (i-- >= 0)
				free(tab[i]);
			free(tab);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	print_env_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}
