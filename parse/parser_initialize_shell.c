/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_initialize_shell.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bernhardbiermann <bernhardbiermann@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:03:01 by bbierman          #+#    #+#             */
/*   Updated: 2024/12/01 12:49:58 by bernhardbie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmds(Token **token_list)
{
	Token	*current;
	int		cmd_count;

	if (!token_list || !*token_list)
		return (0);
	cmd_count = 1;
	current = *token_list;
	while (current)
	{
		if (current->type == T_PIPE)
			cmd_count++;
		current = current->next;
	}
	retrun (cmd_count);
}

int	count_cmd_and_arg(Token **token_list, int cmd_nbr)
{
	Token	*current;
	int		cmd_and_arg_count;
	int		pipe_count;

	cmd_and_arg_count = 0;
	pipe_count = 0;
	current = *token_list;
	while (pipe_count != cmd_nbr)
	{
		if (current->type == T_PIPE)
			pipe_count++;
		current = current->next;
	}
	while (current && current->type != T_PIPE)
	{
		if (current->type == T_TEXT)
		{
			cmd_and_arg_count++;
			current = current->next;
		}
		else
			current = current->next->next;
	}
	return (cmd_and_arg_count);
}

int	count_redirect(Token **token_list, int cmd_nbr)
{
	Token	*current;
	int		redirect_count;
	int		pipe_count;

	redirect_count = 0;
	pipe_count = 0;
	current = *token_list;
	while (pipe_count != cmd_nbr)
	{
		if (current->type == T_PIPE)
			pipe_count++;
		current = current->next;
	}
	while (current && current->type != T_PIPE)
	{
		if (current->type == T_TEXT)
			current = current->next;
		else
		{
			redirect_count++;
			current = current->next->next;
		}
	}
	return (redirect_count);
}

void	initialize_shell(t_shell *data, Token *token_list, t_env *myenvp)
{
	int	cmd_count;

	cmd_count = 0;
	data->nb_cmds = count_cmds(&token_list);
	data->cmds = safe_malloc_shell((sizeof(t_cmd) * data->nb_cmds), data);
	data->pipes = NULL;
	data->env = myenvp;
	data->last_exit_status = 0;
	data->err_msg = NULL;
	while (cmd_count < data->nb_cmds)
	{
		data->cmds[cmd_count].path = NULL;
		data->cmds[cmd_count].cmd = NULL;
		data->cmds[cmd_count].arg_count = \
		count_cmd_and_arg(token_list, cmd_count);
		data->cmds[cmd_count].arg = safe_malloc_shell((sizeof(char *) * \
		(data->cmds[cmd_count].arg_count + 1)), data);
		data->cmds[cmd_count].redirect_count = \
		count_redirect(token_list, cmd_count);
		data->cmds[cmd_count].redirect = \
		safe_malloc_shell((sizeof(t_redirect) \
		* data->cmds[cmd_count].redirect_count), data);
		cmd_count++;
	}
}
