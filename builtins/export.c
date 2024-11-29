/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:51:55 by aroux             #+#    #+#             */
/*   Updated: 2024/11/19 12:22:10 by aroux            ###   ########.fr       */
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

t_env	*ft_export(char *input, t_env *env)
{
	int		key_len;
	char	*equal_ptr;
	t_env	*lst_ptr;
	char	**vars;

	if (input == NULL)
	{
		print_env(env);
		return (env);
	}
	vars = ft_split(input, ' ');
	if (!vars)
		return (NULL);
	while (*vars)
	{
		if (!ft_strchr(*vars, '=')) // if export VAR called without equal sign
			// create VAR. check for maxlen?/ invalid format (alphanumerical only)?
		else	/* update the value in case export VAR=xxx */
		{ // inside the loop logic might go to another function
			equal_ptr = ft_strchr(*vars, '=');
			key_len = ft_strlen(*vars) - ft_strlen(equal_ptr);
			lst_ptr = env;
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

		/* if (!ft_strchr(input, '='))
			new_envp[envp_size] = ft_strdup(input);
		else
		{
			var_name = ft_strdnup(input, (int)(strchr(input, '=') - input));
			value = ft_strdup(input + strchr(input, '='));
			new_envp[envp_size] = multi_strjoin(var_name, "=", value);
			free(var_name);
			free(value);
		} */