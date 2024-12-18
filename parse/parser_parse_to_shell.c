/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_parse_to_shell.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:58:28 by bbierman          #+#    #+#             */
/*   Updated: 2024/12/17 16:26:07 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_redir(t_shell *data, t_Token **current_token, int redir_c, int cmd_c)
{
	t_Token	*current;
	
	current = *current_token;
	if (current->type == T_INPUT)
		data->cmds[cmd_c].redir[redir_c].infile = \
		ft_strdup(current->next->value);
	else if (current->type == T_OUTPUT)
		data->cmds[cmd_c].redir[redir_c].trunc = \
		ft_strdup(current->next->value);
	else if (current->type == T_APPEND)
		data->cmds[cmd_c].redir[redir_c].append = \
		ft_strdup(current->next->value);
	else
		data->cmds[cmd_c].redir[redir_c].here_delim = \
		ft_strdup(current->next->value);
	return (1);
}

t_Token	*setup_cmds_in_shell(t_shell *data, t_Token *current, int cmd_c)
{
	int		arg_c;
	int		redir_c;
	
	arg_c = 0;
	redir_c = 0;
	while (current && current->type != T_PIPE)
	{
		if (current->type == T_TEXT && arg_c < data->cmds[cmd_c].arg_count)
		{
			data->cmds[cmd_c].cmd[arg_c] = ft_strdup(current->value);
			arg_c++;
			current = current->next;
		}
		else if (redir_c < data->cmds[cmd_c].redirect_count)
		{
			redir_c += process_redir(data, &current, redir_c, cmd_c);
			current = current->next->next;
		}
		else
			current = current->next;
	}
	return (current);
}

void	fill_shell(t_shell *data, t_Token **token_list)
{
	t_Token	*current;
	int		cmd_c;

	current = *token_list;
	cmd_c = 0;
	if (current->type == T_ERROR)
	{
		data->last_exit_status = current->length;
		data->err_msg = ft_strdup(current->value);
		return ;
	}
	while (current && cmd_c < data->nb_cmds)
	{
		current = setup_cmds_in_shell(data, current, cmd_c);
		if (current && current->type == T_PIPE)
			current = current->next;
		cmd_c++;
	}
}

void	parse_to_shell(t_shell*	data, t_Token **token_list, t_env *my_envp)
{
	initialize_shell(data, *token_list, my_envp);
	fill_shell(data, token_list);
}
