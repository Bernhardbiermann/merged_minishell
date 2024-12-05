/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:20:27 by aroux             #+#    #+#             */
/*   Updated: 2024/12/05 16:49:29 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* 4.12: we first check if there is only one cmd, or if we have to create pipes in case of more cmds */
void	execute(t_shell *data)
{
	if (data->nb_cmds <= 1 && is_builtin(data, 0) == 1) // if there is only one cmd and it is a builtin, we execute it. If it's not a builtin, we have to create a child process
		exec_cmd(data, 0);
	else
		exec_more_cmds(data);
}

/* This function iterates over the nb of cmds, and for each cmd:
	pipes if it's not the last cmd
	forks to create a child process that redirects what needs redirecting, and executes the builtin or the cmd
	parent process closes pipe ends that are not useful and waits for the children to terminate

	At the moment: not working, I'm getting messages about dup2 that failed which I could not fix,
	but the pipe logic worked at some point. Need to implement the redirection logic and then work from here.
*/
void	exec_more_cmds(t_shell *data)
{
	int		i;
	int		fd[2];
	pid_t	pid;
	int		prev_fd;
	//int		status;

	i = 0;
	prev_fd = -1;
	while (i < data->nb_cmds)
	{
		if (i != data->nb_cmds - 1 && pipe(fd) == -1)
			error_handle("pipe failed", EXIT_FAILURE);
		pid = fork();
		if (pid < 0)
			error_handle("fork failed", EXIT_FAILURE);
		else if (pid == 0)
			child_process(data, i, fd, &prev_fd);
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (i != data->nb_cmds - 1)
			{
				close(fd[1]);
				prev_fd = fd[0];
			}
 			if (i > 0)
			{
				if (dup2(fd[0], STDIN_FILENO) == -1)
					error_handle("dup2 failed: parent", EXIT_FAILURE);
				close(fd[0]);
			}
		}
		i++;
	}
	// 4.12: when child process is created and then exits, it sends back 2 values; its exit status (failure or success) 
	// and a pid_t value sent to the parent to tell it to wait or tell it the process has died (=it is finished)
	//while (wait(&status) > 0) // we execute wait as long as there are still child processes running
	//	;
	// here implement function to collect the last exit status
	while (i-- > 0)
		wait(NULL);
}

void	child_process(t_shell *data, int i, int *fd, int *prev_fd)
{
	int	fd_in;	// only for testing, will go out once redirection is set up
	int	fd_out; // only for testing, will go out once redirection is set up

	if (i != 0)
		close(fd[0]);
	if (*prev_fd != -1) // If there's a previous pipe, read from it
	{
		if (dup2(*prev_fd, STDIN_FILENO) == -1)
		{	
			perror("dup2 failed: child");
			exit(EXIT_FAILURE);
		}
		close(*prev_fd); // Close after duplicating
	}
	if (i != data->nb_cmds - 1) // If not last command, write to the current pipe
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else if (i == data->nb_cmds - 1) // HERE IT WAS JUST TO TEST THE PIPES, but we have to implement a proper redirection logic
	{
		fd_out = open("out_test", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
			error_handle("Failed to open output file", EXIT_FAILURE);
		if (dup2(fd_out, STDOUT_FILENO) == -1) // Redirect stdout to the output file
			error_handle("dup2 failed fd_out", EXIT_FAILURE);
		close(fd_out);          // Close file descriptor after duplication
	}
	if (data->cmds[i]->redir->infile) //redirection fd_in
	{
		fd_in = open(data->cmds[i]->redir->infile, O_RDONLY);
		if (fd_in < 0)
			error_handle("Failed to open input file", EXIT_FAILURE);
		if (dup2(fd_in, STDIN_FILENO) == -1)
			error_handle("dup2 failed fd_in", EXIT_FAILURE);
		close(fd_in);
	}
	// before executing, we have to check if there is a redirection. I liked Fabbio's approach to redirection (see below)
	exec_cmd(data, i);
}

/* executes each command
	if it's a builtin, executes it and then has to clean and exit
	if it's not, check for a valid path, and execve() exits and cleans */
void	exec_cmd(t_shell *data, int i)
{
	char	**env_tab;

	if (is_builtin(data, i))
	{
		//exec_builtin(data->cmds[i]->cmd_name, i); // function to be implemented and exit(EXIT_SUCCESS)
		printf("execute builtin function\n");
	}
	else
	{
		find_cmd_path(data, i);
		env_tab = env_to_tab(data->env);
		printf("Child %d executing command: %s\n", i, data->cmds[i]->path);
		if (execve(data->cmds[i]->path, data->cmds[i]->cmd, env_tab) == -1) // seems to work when tested on a smaller scale
		{
			free_tab(env_tab);
			//other frees?? free_exit_shell() function to implement
			error_handle("execve failed", EXIT_FAILURE);
		}
	}
}

/* four types of redirection, defined at parsing stage:
- truncate  >  (overwrites whatever was in the output file)
- append    >> (appends what is in the output file)
- input 	<  (defines an input file that's gonna be the new end to read)
- heredoc	>> (creates a file delimitated by an EOF mark, that the user can append)
How Fabbio and his partner handled it: if they have a list of token, they check token->type = COMMAND, 
and if token->next->type = redirection (trunc, append, input or heredoc), then we redirect the fd_in or the fd_out
 */

