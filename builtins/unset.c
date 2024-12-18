/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:35 by aroux             #+#    #+#             */
/*   Updated: 2024/12/18 14:03:49 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*search_target_and_delete(t_env *current_input, char *key)
{
	t_env	*current;
	t_env	*tmp;

	current = current_input;
	if (ft_strcmp(current->next->key, key) == 0)
	{
		tmp = current->next;
		current->next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	else
		current = current->next;
	return (current);
}

void	ft_unset(t_shell *data, char **args)
{
	int		i;
	t_env	*current;

	i = 1;
	if (args[i] == NULL)
		return ;
	while (args[i])
	{
		if (is_valid_var_name(args[i]) != 0)
		{
			ft_printf("minishell: export: `%s': not a valid identifier", \
			args[i]);
			data->last_exit_status = 1;
			i++;
			continue ;
		}
		current = data->env;
		while (current && current->next)
			current = search_target_and_delete(current, args[i]);
		i++;
	}
}
