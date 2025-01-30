/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:25:00 by aroux             #+#    #+#             */
/*   Updated: 2025/01/29 12:29:50 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	check_signal_received(t_shell *data)
{
	if (g_signal_received == 1)
		data->last_exit_status = 130;
	if (g_signal_received == 2)
		data->last_exit_status = 131;
	g_signal_received = 0;
}

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
		return (1);
	while (1)
	{	
		input = readline("minishell> ");
		check_signal_received(data);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (parser(data, input, my_envp) == 0)
			execute(data, my_envp);
		clean_shell_struct(data, input);
	}
	if (data)
		free_shell_struct(data, my_envp);
	return (0);
}
