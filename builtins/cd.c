/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:08 by aroux             #+#    #+#             */
/*   Updated: 2024/11/15 13:17:04 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* change directory to the specified path
	if no path is provided, it should switch to the user's home directory 
	chdir already interprets .. and . properly */
/* also update your oldpwd (see export): 
"If, during the execution of the above steps, the PWD environment  variable 
	is  set, the OLDPWD environment variable shall also be set to the value 
	of the old working directory (that is the current working  directory 
	immediately prior to the call to cd)." */
void	ft_cd(const char *path)
{
	if (path == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
		{
			perror("No home directory set");
			return ;
		}
	}
	if (chdir(path) == 0)
		return ;
	else
		perror("No such file or directory");
}

/* function to update OLDPWD in the envp */
void 	update_old (t_shell *shell, char *old)

/* update PWD in the env vars */
int 	env_var_update (t_shell *shell, char *old, char *new)