/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:51:55 by aroux             #+#    #+#             */
/*   Updated: 2025/01/28 12:21:49 by aroux            ###   ########.fr       */
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
			current->value = ft_strdup(equal_ptr + 1);
			free(key);
			break ;
		}
		current = current->next;
	}
	if (!current)
		create_newnode_and_append(data, equal_ptr, key);
}

static void	set_exitstatus_and_print(t_shell *data, char **args, int i)
{
	ft_printf("minishell: `%s': not a valid identifier\n", args[i]);
	data->last_exit_status = 1;
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
			set_exitstatus_and_print(data, args, i);
		else if (!ft_strchr(args[i], '='))
		{
			i++;
			continue ;
		}
		else if (check_name_and_empty_value(args[i]) != 0)
			set_exitstatus_and_print(data, args, i);
		else
			expand_env(data, args[i]);
		i++;
	}
}
