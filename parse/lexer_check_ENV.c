/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_ENV.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:41:11 by bbierman          #+#    #+#             */
/*   Updated: 2024/11/29 11:03:40 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_key_and_exchange_value_in_ENV(t_env *my_envp, Token *current)
{
	t_env	*env_node;

	env_node = my_envp;
	while (env_node)
	{
		if (ft_strcmp(env_node->key, current->value) == 0)
		{
			free(current->value);
			current->value = ft_strdup(env_node->value);
			current->length = ft_strlen(current->value);
			return ;
		}
		env_node = env_node->next;
	}
	free(current->value);
	current->value = ft_strdup("");
	current->length = ft_strlen(current->value);
}

void	find_key_and_exchange_value_in_DQUOT(t_env *my_envp, \
Token *current, char *start)
{
	char	*key;
	char	*old_key;
	char	*value;
	char	*end;
	
	while (start)
	{
		if (start[1] == '?' || start[1] == '$' || start[1] == ' ' \
		|| start[1] == '\0')
			replace_special_value(current, start);
		else
		{
			end = find_end(start + 1);
			key = ft_strncpy(current->value, start + 1, end);
			old_key = ft_strncpy(current->value, start, end);
			value = compare_key_and_get_value(my_envp, key);  // in the function, if value not found in ENV, return '\0' (or "")
			replace_value(current, old_key, value);
			three_frees(key, old_key, value);
		}
		current->length = ft_strlen(current->value);
		start = ft_strchr(current->value, '$');
	}
}

char	*compare_key_and_get_value(t_env *my_envp, char* key)
{
	t_env	*env_node;	

	env_node = my_envp;
	while (env_node)
	{
		if (env_node->key && ft_strcmp(env_node->key, key) == 0)
			return (ft_strdup(env_node->value));
		env_node = env_node->next;
	}
	return (ft_strdup(""));
}

void	find_mask_and_exchange(Token *current, char *start)
{
	while (start)
	{
		replace_value(current, "\r", "$");
		current->length = ft_strlen(current->value);
		start = ft_strchr(current->value, '\r');
	}
}

void	do_env_in_DQUOT_and_ENV(Token *token_list, t_env *my_envp)
{
	Token	*current;
	char	*start;
	char	*next;

	current = token_list;
	start = NULL;
	next = NULL;
	while (current)
	{
		if (current->type == T_ENV)
			find_key_and_exchange_value_in_ENV(my_envp, current);
		if (current->type == T_D_QUOT && \
		((start = ft_strchr(current->value, '$')) != NULL ))
		{
			find_key_and_exchange_value_in_DQUOT(my_envp, current, start);
			if ((next = ft_strchr(current->value, '\r')) != NULL)
				find_mask_and_exchange(current, next);
		}
		current = current->next;
	}
}
