/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:25:00 by aroux             #+#    #+#             */
/*   Updated: 2024/11/29 11:28:10 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	**my_envp;
	char	**env_tab;
	t_shell	*data;

	/* check nb of argvs */
	if (argc != 1 || argv[0] == NULL)
		printf("Wrong nb of arguments\n");

	/* env var list */
	my_envp = create_myenvp(envp);		// create the env vars linked list
	env_tab = env_to_tab(*my_envp);		// convert it to a tab (char **)
	
	print_env(*my_envp);
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
		parser(input, my_envp);
		free(input);
	}

	/* TESTING EXECUTION PART */
	/* create cmds (just for testing pipes, to be removed) */
	//create_cmds(data);
	//print_cmds(data); 		// print cmds to see if properly created

/*	TESTING PATHS FINDING PROCESS, ALL LOOKS TO WORK FINE
     char    **paths;
    paths = ft_split(get_path(env_tab) + 5, ':');  // Skip "PATH="
    if (!paths) {
        error_handle("PATH not found", 0);
    }
	char    *cmd_path;
    char    **cmd_and_args;
	for (int i = 0; i <= 2; i++){
	cmd_and_args = data->cmds[i]->cmd;
    cmd_path = find_valid_path(data->cmds[i]->cmd_name, paths);
	free(data->cmds[i]->path);
	data->cmds[i]->path = cmd_path;
	data->cmds[i]->cmd = cmd_and_args;
    // Step 3: Test and print the result
    if (cmd_path) {
        printf("find_valid_path() found: %s\n", data->cmds[i]->path);
		for (int j = 0; j <= 2; j++){
			if (data->cmds[i]->cmd[j])
				printf("cmd and args: %s\n", data->cmds[i]->cmd[j]);
		}
		pid_t pid = fork();
		if (pid == 0){
		if (execve(data->cmds[1]->path , data->cmds[1]->cmd, env_tab) == -1) {
                perror("execve failed");
                free(cmd_path);
                exit(EXIT_FAILURE);
            }

            free(cmd_path); 
		}
    } else {
        printf("find_valid_path() could not find the command.\n");
    }} */


	/* execute */
	//exec_more_cmds(data); // remove my_envp as it is part of the data->env ?

	/* free the people */
	free_env_list(my_envp, NULL, NULL);
	//free_tab(env_tab);
	if (data)
		free_shell_struct(data);
	return (0);
}

void	free_shell_struct(t_shell *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_cmds)
	{
		if (data->cmds[i]->path)
		{
			free(data->cmds[i]->path);
			free(data->cmds[i]->cmd_name);
			if (data->cmds[i]->cmd)
			{
				j = 0;
				while (data->cmds[i]->cmd[j])
					free(data->cmds[i]->cmd[j++]);
				free(data->cmds[i]->cmd);
			}
			free(data->cmds[i]);
		}
		i++;
	}
	free(data->cmds);
	free(data);
}

void	print_cmds(t_shell *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_cmds)
	{
		printf("Command %d:\n", i + 1);
		printf("  Path: %s\n", data->cmds[i]->path);
		printf("  Cmd Name: %s\n", data->cmds[i]->cmd_name);
		if (data->cmds[i]->cmd)
		{
			j = 0;
			while (data->cmds[i]->cmd[j] != NULL)
			{
				printf("  Arg[%d]: %s\n", j, data->cmds[i]->cmd[j]);
				j++;
			}
		}
		else
			printf("  No arguments found.\n");
		i++;
	}
}

t_shell	*init_shell_struct(t_env *env)
{
	t_shell	*data;
	int		i;

	data = malloc(sizeof(t_shell));
	if (!data)
		return (NULL);
	data->cmds = malloc(3 * sizeof(t_cmd *));
	if (!data->cmds)
	{
		free(data);
		return (NULL);
	}
	i = 0;
	data->nb_cmds = 3;
	while (i < data->nb_cmds)
	{
		data->cmds[i] = malloc(sizeof(t_cmd));
		if (!data->cmds[i])
		{
			while (--i >= 0)
				free(data->cmds[i]);
			free(data->cmds);
			free(data);
			return (NULL);
		}
		data->cmds[i]->path = NULL;
		data->cmds[i]->cmd_name = NULL;
		data->cmds[i]->cmd = NULL;
		i++;
	}
	data->pipes = NULL;
	data->env = env;
	data->infile = NULL;
	data->outfile = NULL;
	return (data);
}

void	create_cmds(t_shell *data)
{
	// Command 1: grep apple
	data->cmds[0]->path = strdup("/bin/grep"); // Full path to executable
	data->cmds[0]->cmd_name = strdup("grep");  // Command name
	data->cmds[0]->cmd = malloc(3 * sizeof(char *));
	data->cmds[0]->cmd[0] = strdup("grep");
	data->cmds[0]->cmd[1] = strdup("apple");
	data->cmds[0]->cmd[2] = NULL;

	// Command 2: sort
	data->cmds[1]->path = strdup("/bin/sort");
	data->cmds[1]->cmd_name = strdup("sort");
	data->cmds[1]->cmd = malloc(2 * sizeof(char *));
	data->cmds[1]->cmd[0] = strdup("sort");
	data->cmds[1]->cmd[1] = NULL;

	// Command 3: uniq
	data->cmds[2]->path = strdup("/bin/uniq");
	data->cmds[2]->cmd_name = strdup("uniq");
	data->cmds[2]->cmd = malloc(2 * sizeof(char *));
	data->cmds[2]->cmd[0] = strdup("uniq");
	data->cmds[2]->cmd[1] = NULL;
}