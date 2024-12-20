/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:49:07 by bbierman          #+#    #+#             */
/*   Updated: 2024/12/20 10:37:09 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_shell_commands(t_shell *data)
{
	for (int i = 0; i < data->nb_cmds; i++) // Schleife über alle Befehle
	{
		printf("Command %d:\n", i + 1);

		// Argumente ausgeben
		printf("  Arguments: ");
		for (int j = 0; data->cmds[i].cmd[j] != NULL; j++)
		{
			printf("\n    %s", data->cmds[i].cmd[j]);
		}
		printf("\n");

		// Umleitungen ausgeben
		printf("  Redirections:\n");
		for (int k = 0; k < data->cmds[i].redirect_count; k++) // Schleife über alle Redirects
		{
			t_redirect *redir = &data->cmds[i].redir[k];
			switch (redir->type)
			{
				case T_INPUT:
					printf("    Input (<): %s\n", redir->filename);
					break;
				case T_OUTPUT:
					printf("    Output (>): %s\n", redir->filename);
					break;
				case T_APPEND:
					printf("    Append (>>): %s\n", redir->filename);
					break;
				case T_HEREDOC:
					printf("    Here-Document (<<): FD: %d\n", redir->fd_heredoc);
					break;
				default:
					printf("    Unknown redirection type\n");
			}
		}
		printf("\n");
	}
}