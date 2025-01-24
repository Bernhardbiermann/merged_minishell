/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:24:34 by aroux             #+#    #+#             */
/*   Updated: 2025/01/24 12:25:00 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	append_to_lst(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}

t_env	*fill_env_node(char *env_var, t_env **my_envp)
{
	t_env	*new;
	char	*key;
	char	*value;
	int		length;

	length = ft_strlen(env_var) - ft_strlen(ft_strchr(env_var, '='));
	key = ft_substr(env_var, 0, length);
	if (!key)
		return (NULL);
	value = ft_strdup(ft_strchr(env_var, '=') + 1);
	if (!value)
	{
		free(key);
		return (NULL);
	}
	new = create_env_node(key, value);
	if (!new)
	{
		free(key);
		free(value);
		return (NULL);
	}
	append_to_lst(my_envp, new);
	return (new);
}

t_env	**create_myenvp(char **envp)
{
	t_env	**my_envp;

	my_envp = malloc(sizeof(t_env *));
	if (!my_envp)
		return (NULL);
	*my_envp = NULL;
	while (*envp)
	{
		if (!(fill_env_node(*envp, my_envp)))
		{
			free_env_list(my_envp, NULL, NULL);
			return (NULL);
		}
		envp++;
	}
	return (my_envp); 
}

void	free_env_list(t_env **my_envp, char *key, char *value)
{
	t_env	*current;
	t_env	*next;

	if (!my_envp)
		return ;
	if (key)
		free(key);
	if (value)
		free(value);
	current = *my_envp;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	free(my_envp);
}
