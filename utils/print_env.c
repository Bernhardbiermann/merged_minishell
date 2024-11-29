/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:17:27 by aroux             #+#    #+#             */
/*   Updated: 2024/11/28 14:27:53 by aroux            ###   ########.fr       */
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

/* bubble sort algo to sort the entries alphabetically*/
/* pb here i cannot directly compare t_env vars, need to convert them to strings*/
/* t_env	**sort_env(t_env **env, int env_len)
{
	int		i;
	t_env	*tmp;

	while (env_len > 1)
	{
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(env[i]->key, env[i + 1]->key) > 0)
			{
				tmp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = tmp;
			}
			i++;
		}
		env_len--;
	}
	return (env);
} */
