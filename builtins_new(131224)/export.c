/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:51:55 by aroux             #+#    #+#             */
/*   Updated: 2024/12/13 16:49:32 by bbierman         ###   ########.fr       */
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
	if (!isalpha(str[0]) && str[0] != '_') //131224 B: First char has to be alpha or underscore
		return (1);
	while (str[i])
	{
		if (!isalnum(str[i]) && str[i] != '_') //131224 B: Next one can also be a number
			return (1);
		i++;
	}
	return (0);
}

t_env	*ft_export(char **args, t_shell *data)
{
	int		key_len;
	char	*equal_ptr;
	t_env	*current;
	int		i;
	int		j;

	if (args == NULL)
	{
		print_env(data->env);
		return (data->env);
	}
	i = 1;
	while (args[i])
	{
		if (!ft_strchr(args[i], '=') && is_valid_var_name(args[i]) != NULL)
		{
			ft_printf("minishell: export: `%s': not a valid identifier", args[i]);
			data->last_exit_status = 1;
			continue ;
		}
		else if (!ft_strchr(args[i], '=')) // 131224 B: the potential varibal will be safed in export but not in env
			continue ;
		else	/* update the value in case export VAR=xxx */
		{ // inside the loop logic might go to another function
			equal_ptr = ft_strchr(args[i], '=');
			key_len = ft_strlen(args[i]) - ft_strlen(equal_ptr);
			while (lst_ptr && ft_strncmp(*vars, lst_ptr->key, key_len) != 0)
				lst_ptr = lst_ptr->next;
			free(lst_ptr->value);
			if (ft_strlen(equal_ptr) > 1) // if something after equal sign, update value
				lst_ptr->value = ft_strdup(equal_ptr + 1);
			else
				lst_ptr->value = NULL;
		}
		vars++;
	}
	return (env);
}
