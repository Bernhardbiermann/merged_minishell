/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:25:00 by aroux             #+#    #+#             */
/*   Updated: 2025/01/14 16:27:43 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_env	**my_envp;
	t_shell	*data;

	if (argc != 1 || argv[0] == NULL)
		printf("Wrong nb of arguments\n");
	my_envp = create_myenvp(envp);
	data = init_shell_struct(*my_envp);	
	if (!data)
	{
		printf("Failed to initialize shell struct.\n");
		return (1);
	}
	while (1)
	{	
		input = readline("minishell> ");
		if (!input)
			break ;
		if (input[0] == '\0')
			continue ;
		if (*input)
			add_history(input);	
		parser(data, input, my_envp);
		if (check_t_error(data) == 0)
			execute(data, my_envp);
		free(input);
		clean_shell_struct(data);
	}
	if (data)
		free_shell_struct(data, my_envp);
	return (0);
}
