/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:24:28 by aroux             #+#    #+#             */
/*   Updated: 2025/01/24 12:05:35 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* function to free all the elements of a double array */
void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_nullify(void *to_be_freed)
{
	if (to_be_freed)
	{
		free(to_be_freed);
		to_be_freed = NULL;
	}
}

void	free_many_splits(char **split1, char **split2)
{
	if (split1)
		free_tab(split1);
	if (split2)
		free_tab(split2);
}

void	free_cmds_close_files(int i, char ***cmds, int infile, int outfile)
{
	while (i-- > 0)
		free_tab(cmds[i]);
	free(cmds);
	close_fd(infile);
	close_fd(outfile);
	exit(-1);
}
