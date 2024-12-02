/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bernhardbiermann <bernhardbiermann@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:58:28 by bbierman          #+#    #+#             */
/*   Updated: 2024/12/01 15:35:36 by bernhardbie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_redir(t_shell *data, Token **token_list, int redir_count)
{
	Token	*current;

	current = current->next;
	if (current->type == T_INPUT)
		data->cmds[cmd_count].redirect[redir_count].in = \
ft_strdup(current->value);
	else if (current->type == T_OUTPUT)
		data->cmds[cmd_count].redirect[redir_count].out = \
ft_strdup(current->value);
	else if (current->type == T_APPEND)
		data->cmds[cmd_count].redirect[redir_count].append = \
ft_strdup(current->value);
	else
		data->cmds[cmd_count].redirect[redir_count].heredoc = \
ft_strdup(current->value);
					redir_count++;
					current = current->next;

}

void	fill_shell(t_shell *data, Token **token_list)
{
	Token	*current;
	t_cmd	*current_cmd;
	int		cmd_count;
	int		arg_count;
	int		redir_count;

	current = *token_list;
	current_cmd = data->cmds;
	cmd_count = 0;
	if (current->type == T_ERROR)
	{
		data->last_exit_status = current->length;
		data->err_msg = ft_strdup(current->value);
		return ;
	}
	while (current)
	{
		while (current->type != T_PIPE && cmd_count < data->nb_cmds)
		{
			arg_count = 0;
			redir_count = 0;
			while (arg_count < data->cmds[cmd_count].arg_count && \
			redir_count < data->cmds[cmd_count].redirect_count)
			{
				if (current->type == T_TEXT)
				{
					data->cmds[cmd_count].arg[arg_count] = \
					ft_strdup(current->value);
					arg_count++;
					current = current->next;
				}
				else
				{
					current = current->next;
					if (current->type == T_INPUT)
						data->cmds[cmd_count].redirect[redir_count].in = \
						ft_strdup(current->value);
					else if (current->type == T_OUTPUT)
						data->cmds[cmd_count].redirect[redir_count].out = \
						ft_strdup(current->value);
					else if (current->type == T_APPEND)
						data->cmds[cmd_count].redirect[redir_count].append = \
						ft_strdup(current->value);
					else
						data->cmds[cmd_count].redirect[redir_count].heredoc = \
						ft_strdup(current->value);
					redir_count++;
					current = current->next;
				}
			}
			cmd_count++;
		}
	}
}

void	parse_to_shell(t_shell*	data, Token **token_list, t_env *my_envp)
{
	initialize_shell(data, token_list, my_envp);
	fill
	
}