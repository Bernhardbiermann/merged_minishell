/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:06:22 by aroux             #+#    #+#             */
/*   Updated: 2024/12/18 15:06:55 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* useful to check result of the parsing input in the execution? */
void	print_cmds(t_shell *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_cmds)
	{
		printf("Command %d:\n", i + 1);
		printf("  Path: %s\n", data->cmds[i].path);
		printf("  Cmd Name: %s\n", data->cmds[i].cmd[0]);
		if (data->cmds[i].cmd)
		{
			j = 0;
			while (data->cmds[i].cmd[j] != NULL)
			{
				printf("  Arg[%d]: %s\n", j, data->cmds[i].cmd[j]);
				j++;
			}
		}
		else
			printf("  No arguments found.\n");
		i++;
	}
}


void	create_cmds(t_shell *data)
{
	// Command 1: grep apple
	data->cmds[0].path = ft_strdup("/bin/grep"); // Full path to executable
	data->cmds[0].cmd = malloc(3 * sizeof(char *));
	data->cmds[0].cmd[0] = ft_strdup("grep");
	data->cmds[0].cmd[1] = ft_strdup("apple");
	data->cmds[0].cmd[2] = NULL;
	data->cmds[0].redir = malloc(sizeof(t_redirect));
    data->cmds[0].redir->infile = ft_strdup("test.txt");
    data->cmds[0].redir->trunc = NULL; // No output redirection
	data->cmds[0].redir->append = NULL; // No output redirection

	// Command 2: sort
	data->cmds[1].path = ft_strdup("/bin/sort");
	data->cmds[1].cmd = malloc(2 * sizeof(char *));
	data->cmds[1].cmd[0] = ft_strdup("sort");
	data->cmds[1].cmd[1] = NULL;
	data->cmds[1].redir = malloc(sizeof(t_redirect));
    data->cmds[1].redir->infile = NULL; // No input redirection
	data->cmds[1].redir->trunc = NULL; // No output redirection
	data->cmds[1].redir->append = NULL; // No output redirection

	// Command 3: uniq
	data->cmds[2].path = ft_strdup("/bin/uniq");
	data->cmds[2].cmd = malloc(2 * sizeof(char *));
	data->cmds[2].cmd[0] = ft_strdup("uniq");
	data->cmds[2].cmd[1] = NULL;
    data->cmds[2].redir = malloc(sizeof(t_redirect));
	data->cmds[2].redir->infile = NULL; // Now this is safe.
	data->cmds[2].redir->trunc = NULL; // No output redirection
	data->cmds[2].redir->append = NULL; // No output redirection
}
