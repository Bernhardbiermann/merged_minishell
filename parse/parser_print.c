/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:49:07 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/21 14:14:21 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_shell_commands(t_shell *data)
{
	t_redir	*redir;
	t_hdoc	*current;

	for (int i = 0; i < data->nb_cmds; i++)
	{
		printf("Command %d:\n", i + 1);
		printf("  Arguments: ");
		for (int j = 0; data->cmds[i].cmd[j] != NULL; j++)
		{
			printf("\n    %s", data->cmds[i].cmd[j]);
		}
		printf("\nnumber of cmd/args: %d\n", data->cmds[i].arg_count);
		printf("\n");
		printf("  Redirections:\n");
		for (int k = 0; k < data->cmds[i].redirect_count; k++)
		{
			redir = &data->cmds[i].redir[k];
			switch (redir->type)
			{
				case T_INPUT:
				{
					printf("    Input (<): %s\n", redir->filename);
					printf("    last_in_heredoc: %d\n", redir->last_redir_in);
					break ;
				}
				case T_OUTPUT:
				{
					printf("    Output (>): %s\n", redir->filename);
					printf("    last_in_heredoc: %d\n", redir->last_redir_in);
					break ;
				}
				case T_APPEND:
				{
					printf("    Append (>>): %s\n", redir->filename);
					printf("    last_in_heredoc: %d\n", redir->last_redir_in);
					break ;
				}
				case T_HEREDOC:
				{
					printf("    Here-Document (<<): %s\n", redir->hdoc_delim);
					printf("    last_in_heredoc: %d\n", redir->last_redir_in);
					break ;
				}
				default :
					printf("    Unknown redirection type\n");
			}
		}
		printf("\n");
	}
	if (data->hdoc)
	{
		printf("  Heredoc List:\n");
		current = data->hdoc;
		while (current)
		{
			printf("    Token Value: %s\n", current->delim);
			current = current->next;
		}
	}
	printf("\n");
}
