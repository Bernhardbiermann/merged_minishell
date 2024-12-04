/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:20:27 by aroux             #+#    #+#             */
/*   Updated: 2024/12/04 15:59:23 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* we first check if there is only one cmd, or if we have to create pipes in case of more cmds */
void	execute(t_shell *data)
{
	if (data->nb_cmds <= 1 && is_builtin(data, 0) == 1) // if there is only one cmd and it is a builtin, we execute it. If it's not a builtin, we have to create a child process
		exec_cmd(data, 0);
	else
		exec_more_cmds(data);
}

void	exec_more_cmds(t_shell *data)
{
	int		i;
	int		fd[2];
	pid_t	pid;
	int		status;

	i = 0;
	while (i < data->nb_cmds)
	{
		if (i != data->nb_cmds - 1)
			pipe(fd);
		pid = fork();
		if (pid < 0)
			error_handle("fork failed", EXIT_FAILURE);
		else if (pid == 0)
			child_process(data, i, fd);
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		i++;
	}
	// when child process is created and the exits, it sends back 2 values; its exit status (failure or success) 
	// and a pid_t value sent to the parent to tell it to wait or tell it the process has died (=it is finished)
	while (wait(&status) > 0) // we execute wait as long as there are still child processes running
		;
	// here implement function to collect the last exit status
}

void	child_process(t_shell *data, int i, int *fd)
{
	if (i != 0)
		close(fd[0]);
	if (i != data->nb_cmds - 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	else if (i == data->nb_cmds - 1) // HERE IT WAS JUST TO TEST THE PIPES, but we have to implement a proper redirection logic
	{
		int out_fd = open("out_test", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_fd < 0)
			error_handle("Failed to open output file", EXIT_FAILURE);
		dup2(out_fd, STDOUT_FILENO); // Redirect stdout to the output file
		close(out_fd);          // Close file descriptor after duplication
	}
	if (data->cmds[i]->fd_in != -1) //redirection fd_in
	{
		dup2(data->cmds[i]->fd_in, STDIN_FILENO);
		close(data->cmds[i]->fd_in);
	}
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
		// before executing, we have to check if there is a redirection. I liked Fabbio's approach to redirection (see below)
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

