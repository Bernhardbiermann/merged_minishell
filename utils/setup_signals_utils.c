/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:09:20 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/29 12:29:30 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile sig_atomic_t	g_signal_received;

void	handle_sigint_interactive(int signum)
{
	(void)signum;
	g_signal_received = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_heredoc(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void	handle_sigquit_child(int signum)
{
	(void)signum;
	g_signal_received = 2;
	write(2, "Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
}

void	handle_sigint_child(int signum)
{
	(void)signum;
	g_signal_received = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	//rl_redisplay();
}
