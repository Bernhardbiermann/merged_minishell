/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:24:28 by aroux             #+#    #+#             */
/*   Updated: 2024/11/27 12:59:56 by aroux            ###   ########.fr       */
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

void	free_many_splits(char **split1, char **split2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (split1[i])
	{
		free(split1[i]);
		i++;
	}
	free(split1);
	while (split2[j])
	{
		free(split2[j]);
		j++;
	}
	free(split2);
}

void	free_cmds_close_files(int i, char ***cmds, int infile, int outfile)
{
	while (i-- > 0)
		free_tab(cmds[i]);
	free(cmds);
	if (infile >= 0)
		close(infile);
	if (outfile >= 0)
		close(outfile);
	exit(-1);
}

void	multi_close(int fds[], int size, int infile, int outfile)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(fds[i]);
		i++;
	}
	if (infile >= 0)
		close(infile);
	if (outfile >= 0)
		close(outfile);
	return ;
}
