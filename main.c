/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:25:00 by aroux             #+#    #+#             */
/*   Updated: 2025/01/17 11:34:29 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

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
		if (g_signal_received == 1)
			data->last_exit_status = 130;
		g_signal_received = 0;
		input = readline("minishell> ");
		if (!input)
			break ;
		if (*input)
			add_history(input);	
		if (parser(data, input, my_envp) == 0)
			execute(data, my_envp);
		free(input);
		clean_shell_struct(data);
	}
	if (data)
		free_shell_struct(data, my_envp);
	return (0);
}
