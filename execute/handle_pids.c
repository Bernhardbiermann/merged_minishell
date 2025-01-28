/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pids.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:03:46 by aroux             #+#    #+#             */
/*   Updated: 2025/01/28 16:49:53 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_to_pids_list(t_shell *data, pid_t pid)
{
	t_pids	*newpid;
	t_pids	*current;

	newpid = malloc(sizeof(t_pids));
	if (!newpid)
		return ;
	newpid->pid = pid;
	newpid->next = NULL;
	if (!data->pids)
	{
		data->pids = newpid;
		return ;
	}
	current = data->pids;
	while (current->next)
		current = current->next;
	current->next = newpid;
}

void	wait_for_pids(t_shell *data)
{
	t_pids	*current;
	int		status;

	current = data->pids;
	while (current)
	{
		if (waitpid(current->pid, &status, 0) == -1)
			continue ;
		else if (WIFEXITED(status))
			data->last_exit_status = WEXITSTATUS(status);
		current = current->next;
	}
	return ;
}
