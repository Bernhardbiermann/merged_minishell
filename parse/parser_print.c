/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:49:07 by bbierman          #+#    #+#             */
/*   Updated: 2024/12/09 17:36:27 by bbierman         ###   ########.fr       */
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
			printf("%s ", data->cmds[i].cmd[j]);
		}
		printf("\n");

		// Umleitungen ausgeben
		printf("  Redirections:\n");
		for (int k = 0; k < data->cmds[i].redirect_count; k++) // Schleife über alle Redirects
		{
			if (data->cmds[i].redir[k].infile)
				printf("    Input (<): %s\n", data->cmds[i].redir[k].infile);
			if (data->cmds[i].redir[k].trunc)
				printf("    Output (>): %s\n", data->cmds[i].redir[k].trunc);
			if (data->cmds[i].redir[k].append)
				printf("    Append (>>): %s\n", data->cmds[i].redir[k].append);
			if (data->cmds[i].redir[k].here_delim)
				printf("    Here-Document (<<): %s\n", data->cmds[i].redir[k].here_delim);
		}
		printf("\n");
	}
}