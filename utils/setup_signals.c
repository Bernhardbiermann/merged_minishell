/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:43:45 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/20 18:21:17 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern volatile sig_atomic_t	g_signal_received;

void	setup_signal(int type)
{
	struct sigaction	sa_quit;
	struct sigaction	sa_int;
	
	if (type == INTERACTIVE)
	{
		set_sigaction(&sa_quit, SIG_IGN, SIGQUIT);
		set_sigaction(&sa_int, handle_sigint_interactive, SIGINT);
	}
	else if (type == RESET)
	{
		set_sigaction(&sa_quit, SIG_DFL, SIGQUIT);
		set_sigaction(&sa_int, SIG_DFL, SIGINT);
	}
	else if (type == WAIT)
	{
		set_sigaction(&sa_quit, SIG_IGN, SIGQUIT);
		set_sigaction(&sa_int, SIG_IGN, SIGINT);
	}
	else if (type == HEREDOC)
	{
		set_sigaction(&sa_quit, SIG_IGN, SIGQUIT);
		set_sigaction(&sa_int, handle_sigint_heredoc, SIGINT);
	}
}

void	exit_signal(int exit_status)
{
	printf("Error setting up signal handling, exiting minishell\n");
	exit(exit_status);
}

void	set_sigaction(struct sigaction *sa, void (*f_handler)(int), int signum)
{
	if (sigemptyset(&sa->sa_mask) == -1)
		exit_signal(1);
	sa->sa_flags = 0;
	sa->sa_handler = f_handler;
	if (sigaction(signum, sa, NULL) == -1)
		exit_signal(1);
}

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

