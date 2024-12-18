/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:35 by aroux             #+#    #+#             */
/*   Updated: 2024/12/18 10:51:21 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_shell *data, char **args)
{
	int		i;
	t_env	*current;
	t_env	*tmp;

	i = 1;
	if (args[i] == NULL)
		return ;
	while (args[i])
	{
		if (is_valid_var_name(args[i]) != 0)
		{
			ft_printf("minishell: export: '%s': not a valid identifier", args[i]);
			data->last_exit_status = 1;
			i++;
			continue ;
		}
		current = data->env;
		while (current && current->next)
		{
			if (ft_strcmp(current->next->key, args[i]))
			{
				tmp = current->next;
				current-> next = tmp->next;
				free(tmp->key);
				free(tmp->value);
				free(tmp);
			}
			else
				current = current->next;
		}
		i++;
	}
}