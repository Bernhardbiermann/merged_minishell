/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:52:08 by aroux             #+#    #+#             */
/*   Updated: 2025/01/08 16:54:52 by bbierman         ###   ########.fr       */
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

/* function to update OLDPWD in the envp */

static void	set_errorstatus_and_print_msg(t_shell *data, char *input)
{
	data->last_exit_status = 1;
	ft_printf(input);
}

void	update_pwd(t_shell *data, char *envp_key, char *envp_new_value)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (ft_strcmp(current->key, envp_key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(envp_new_value);
		}
		current = current->next;
	}
}

void	ft_cd(t_shell *data, const char *path, int i)
{
	char	pwd_old[1024];
	char	pwd_new[1024];

	if (data->cmds[i].arg_count > 2)
	{
		set_errorstatus_and_print_msg(data, "cd: too many arguments\n");
		return ;
	}
	if (getcwd(pwd_old, sizeof(pwd_old)) == NULL)
		perror("ft_cd: getcwd failed");
	if (!path)
	{
		path = getenv("HOME");
		if (!path)
			return (perror("No home directory set"));
	}
	if (chdir(path) == 0)
	{
		update_pwd(data, "OLDPWD", pwd_old);
		if (getcwd(pwd_new, sizeof(pwd_new)) != NULL)
			update_pwd(data, "PWD", pwd_new);
		return ;
	}
	set_errorstatus_and_print_msg(data, "cd: No such file or directory\n");
}
