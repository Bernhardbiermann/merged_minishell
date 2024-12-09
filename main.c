/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:25:00 by aroux             #+#    #+#             */
/*   Updated: 2024/12/09 18:02:35 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	**my_envp;
	//char	**env_tab;
	t_shell	*data;

	/* check nb of argvs */
	if (argc != 1 || argv[0] == NULL)
		printf("Wrong nb of arguments\n");

	/* env var list */
	my_envp = create_myenvp(envp);		// create the env vars linked list
	//env_tab = env_to_tab(*my_envp);		// convert it to a tab (char **)
	
	//print_env(*my_envp);
	//print_env_tab(env_tab); 			// see also env.c and export.c in the builtins 

	/* initialize shell struct */
	data = init_shell_struct(*my_envp);	
	if (!data)
	{
		printf("Failed to initialize shell struct.\n");
		return (1);
	}
	while (1) // Prompt anzeigen und Eingabe lesen
	{
		input = readline("minishell> ");
		if (!input) // Falls Benutzer EOF eingibt (Strg+D)
		{
			printf("\nExit minishell.\n");
			break;
		}
		if (*input) 	// Eingabe in die History aufnehmen
			add_history(input);	
		printf("You entered: %s\n", input);
		parser(data, input, my_envp);
		free(input);
	}
	/* free the people */
	free_env_list(my_envp, NULL, NULL);
	//free_tab(env_tab);
	if (data)
		free_shell_struct(data);
	return (0);
}

/*  This function we will use each time we encounter an error, at least in the execution part 
	to be appended to make sure we free everything*/
	
void	free_shell_struct(t_shell *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_cmds)
	{
		if (data->cmds[i].path)
			free(data->cmds[i].path);
		if (data->cmds[i].cmd)
		{
			j = 0;
			while (j < data->cmds[i].arg_count)
			{
				if (data->cmds[i].cmd[j])
					free(data->cmds[i].cmd[j++]);
			}
			free(data->cmds[i].cmd);
		}
		if (data->cmds[i].redir)
		{
			j = 0;
			while (j < data->cmds[i].redirect_count)
			{
				if (data->cmds[i].redir[j].infile)
					free(data->cmds[i].redir[j++].infile);
				if (data->cmds[i].redir[j].trunc)
					free(data->cmds[i].redir[j++].trunc);
				if (data->cmds[i].redir[j].append)
					free(data->cmds[i].redir[j++].append);
				if (data->cmds[i].redir[j].here_delim)
					free(data->cmds[i].redir[j++].here_delim);
			}
			free(data->cmds[i].redir);
		}
		i++;
	}
	if (data->cmds)
		free(data->cmds);
	free(data);
}

t_shell	*init_shell_struct(t_env *env)
{
	t_shell	*data;
	int		i;

	data = malloc(sizeof(t_shell));
	if (!data)
		return (NULL);
	data->nb_cmds = 1;
	data->cmds = malloc(data->nb_cmds * sizeof(t_cmd));
	if (!data->cmds)
	{
		free(data);
		return (NULL);
	}
	i = 0;
	while (i < data->nb_cmds)
	{
		data->cmds[i].path = NULL;
		data->cmds[i].cmd = NULL;
		i++;
	}
	data->env = env;
	return (data);
}
