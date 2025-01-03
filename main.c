/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:25:00 by aroux             #+#    #+#             */
/*   Updated: 2024/12/18 15:07:31 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	**my_envp;
	t_shell	*data;

	/* check nb of argvs */
	if (argc != 1 || argv[0] == NULL)
		printf("Wrong nb of arguments\n");
	/* env var list */
	my_envp = create_myenvp(envp);
	/* initialize shell struct */
	data = init_shell_struct(*my_envp);	
	if (!data)
	{
		printf("Failed to initialize shell struct.\n");
		return (1);
	}

	/* TESTING EXECUTION PART */
	/* create cmds (just for testing pipes, to be removed in the end) 
	Here I am testing for test.txt < grep 'apple' | sort | uniq > out_test 
	*/
	//create_cmds(data);
	//print_cmds(data); 		// print cmds to see if properly created
	
	while (1)
	{	
		if (!data)
			data = init_shell_struct(*my_envp);
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
		execute(data);
		free(input);
		free_shell_struct(data);
		data = NULL;
	}
	/* free the people */
	free_env_list(my_envp, NULL, NULL);
//	if (data)
//		free_shell_struct(data);
	return (0);
}
