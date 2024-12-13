/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:25:00 by aroux             #+#    #+#             */
/*   Updated: 2024/12/12 10:04:05 by bbierman         ###   ########.fr       */
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
		free(input);
		free_shell_struct(data);
		data = NULL;
	}
	/* free the people */
	free_env_list(my_envp, NULL, NULL);
	if (data)
		free_shell_struct(data);
	return (0);
}
