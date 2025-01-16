/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:49:07 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/16 15:25:14 by bbierman         ###   ########.fr       */
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
		printf("\nnumber of cmd/args: %d\n", data->cmds[i].arg_count);
		printf("\n");

		// Umleitungen ausgeben
		printf("  Redirections:\n");
		for (int k = 0; k < data->cmds[i].redirect_count; k++) // Schleife über alle Redirects
		{
			t_redir *redir = &data->cmds[i].redir[k];
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
					printf("    Here-Document (<<): %s\n", redir->filename);
					break;
				default:
					printf("    Unknown redirection type\n");
			}
		}
		printf("\n");

		// Heredoc-Liste ausgeben
		/*if (data->hdoc) // Prüfen, ob die Heredoc-Liste existiert
		{
			printf("  Heredoc List:\n");
			t_hdoc *current = data->hdoc; // Annahme: `hdoc` ist ein Array von Strukturen
			while (current)
			{
				printf("    Token Value: %s\n", current->value);
				current = current->next;
			}
		}
		else
		{
			printf("  No Heredoc List for Command %d\n", i + 1);
		}
		printf("\n");*/
	}
	if (data->hdoc) // Prüfen, ob die Heredoc-Liste existiert
	{
		printf("  Heredoc List:\n");
		t_hdoc *current = data->hdoc; // Annahme: `hdoc` ist ein Array von Strukturen
		while (current)
		{
			printf("    Token Value: %s\n", current->value);
			current = current->next;
		}
	}
	printf("\n");
}
