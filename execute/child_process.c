/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:45:33 by aroux             #+#    #+#             */
/*   Updated: 2024/12/20 13:55:03 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(t_shell *data, int i, int *fd, int *prev_fd)
{
	handle_redirections(&data->cmds[i]);
	if (*prev_fd != -1) // If there's a previous pipe, read from it
	{
		printf("Child %d dup2: prev_fd=%d, fd[1]=%d\n", i, *prev_fd, fd[1]);
		if (dup2(*prev_fd, STDIN_FILENO) == -1)
			error_handle("dup2 failed: child input", EXIT_FAILURE);
		close(*prev_fd); // Close after duplicating
	}
	if (i != data->nb_cmds - 1) // If not last command, write to the current pipe
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1) 
			error_handle("dup2 failed: child output", EXIT_FAILURE);
		close(fd[1]);
	}
//	if (i != 0)
//		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);       // Close current pipe's write end
	if (fd[0] >= 0)
		close(fd[0]); 
	exec_cmd(data, i);
}

/* four types of redirection, defined at parsing stage:
- truncate  >  (overwrites whatever was in the output file)
- append    >> (appends what is in the output file)
- input 	<  (defines an input file that's gonna be the new end to read)
- heredoc	>> (creates a file delimitated by an EOF mark, that the user can append)
How Fabbio and his partner handled it: if they have a list of token, they check token->type = COMMAND, 
and if token->next->type = redirection (trunc, append, input or heredoc), then we redirect the fd_in or the fd_out
 */
void	handle_redirections(t_cmd *cmd)
{
	//t_redirect	*redir;
	int			i;

	//if (!cmd->redir)
	//	return;
	//redir = cmd->redir;
	i = 0;
	while (i < cmd->redirect_count) // 1912A: seems that Nick handled multiple redir by just having a linked list of redirection and using here a while loop
	{
		open_dup_close(cmd->redir[i]);
		i++;
	}
}

void	open_dup_close(t_redirect redir)
{
	int	fd;

	if (redir.type == T_INPUT) // input file
	{
		fd = open(redir.filename, O_RDONLY);
		if (fd < 0)
			error_handle("Failed to open input file", EXIT_FAILURE);
		if (dup2(fd, STDIN_FILENO) == -1)
			error_handle("dup2 failed for input redirection", EXIT_FAILURE);
		close(fd);
	}
	else if (redir.type == T_OUTPUT || redir.type == T_APPEND)
	{
		if (redir.type == T_OUTPUT)
			fd = open(redir.filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(redir.filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			error_handle("Failed to open output file", EXIT_FAILURE);
		if (dup2(fd, STDOUT_FILENO) == -1)
			error_handle("dup2 failed for output redirection", EXIT_FAILURE);
		close(fd);
	}
	//else if (redir.type == T_HEREDOC)
	//	redir_heredoc(redir);
}

/* if heredoc, create pipe for the heredoc (suggested by chatGPT 1912A)*/
void redir_heredoc(t_redirect redir)
{
	int	fd[2];

	if (pipe(fd) == -1)
		error_handle("pipe failed for heredoc", EXIT_FAILURE);
	write(fd[1], redir.filename, 50); // 1912A: to adapt to what is effectively our heredoc form and content
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error_handle("dup2 failed for heredoc", EXIT_FAILURE);
	close(fd[0]);
}