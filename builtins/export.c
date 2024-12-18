/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:51:55 by aroux             #+#    #+#             */
/*   Updated: 2024/12/18 14:55:52 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* export VAR=value creates a new envp variable named VAR with value 'value'
	if VAR exists, it updates its value
	if export VAR is called without value, creates the VAR without value
	if just export is called, it prints the content of envp (CHECK if true in bash)
	you can also export multiple vars: export VAR1=v1 VAR2=v2 VAR3=v3 */
// CHECK1: input might be in another form, maybe already a char** ?
// CHECK2: output format slightly different than env command. Check in bash

int	is_valid_var_name(const char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_') //131224 B: First char has to be alpha or underscore
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_') //131224 B: Next one can also be a number
			return (1);
		i++;
	}
	return (0);
}

char	*safe_malloc(t_shell *data, size_t len)
{
	char	*value;

	value = malloc(len + 1);
	if (!value)
	{
		ft_printf("minishell: export: memory allocation error\n");
		data->last_exit_status = 1;
		return NULL;
	}
	return (value);
}

void	create_newnode_and_append(t_shell *data, char *equal_ptr, char *key)
{
	t_env	*new_node;
	char	*value;

	value = ft_strdup(equal_ptr + 1);
	if (!value)
	{
		ft_printf("minishell: export: memory allocation failed\n");
		data->last_exit_status = 1;
		return ;
	}
	new_node = create_env_node(key, value);
	if (new_node)
		append_to_lst(&data->env, new_node);
	else
		free(value);
}

void	expand_env(t_shell *data, char *input)
{
	int		key_len;
	char	*equal_ptr;
	char	*key;
	t_env	*current;

	equal_ptr = ft_strchr(input, '=');
	key_len = ft_strlen(input) - ft_strlen(equal_ptr);
	key = safe_malloc(data, key_len + 1);
	if (!key)
		return ;
	ft_strlcpy(key, input, key_len + 1);
	current = data->env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = safe_malloc(data, ft_strlen(equal_ptr) + 1);
			if (!current->value)
				break ;
		}
		current = current->next;
	}
	if (!current)
		create_newnode_and_append(data, equal_ptr, key);
	free(key);
}

void	ft_export(char **args, t_shell *data)
{
	int		i;

	if (!args[1])
		print_env(data->env);
	i = 1;
	while (args[i])
	{
		if (!ft_strchr(args[i], '=') && is_valid_var_name(args[i]) != 0)
		{
			ft_printf("minishell: export: `%s': \
			not a valid identifier", args[i]);
			data->last_exit_status = 1;
			continue ;
		}
		else if (!ft_strchr(args[i], '=')) // 131224 B: the potential varibal will be safed in export but not in env
			continue ;
		else
			expand_env(data, args[i]);
		i++;
	}
}
