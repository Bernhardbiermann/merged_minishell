/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:46:58 by aroux             #+#    #+#             */
/*   Updated: 2024/11/29 11:08:19 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* check what i'm actually going to input to the function in the end */
void	exec_cmd(t_shell *data)
{
	// if i only have one command and no pipe
		exec_one_cmd(data);
	// else
		exec_more_cmds(data);
}

void	exec_one_cmd(t_shell *data)
{
	char **env_tab;

/* 	if (is_builtin(data, 0) == 1)
	{	
		printf("builtin function");
		//builtin_functions(data->cmds[0]->cmd_name);
	} */
	if (1) // should be 'else', but I'm skipping the checkin of if the function in a builtin for now
	{
		check_cmd(data, 0); // access() just needs the command path in data->cmds_path?
		env_tab = env_to_tab(data->env);
		execve(data->cmds[0]->path, data->cmds[0]->cmd, env_tab); // check if execve frees what needs freeing
		perror("One cmd execve failed"); // define
		free(env_tab);
		//free_all();  // TO IMPLEMENT
		exit(EXIT_FAILURE);
	}
}

void	exec_more_cmds(t_shell *data)
{
	int		i;
	pid_t	*pids;  // existera normalement dnas le struct

	if (!(data->pipes = malloc((data->nb_cmds - 1) * sizeof(int *))))
		error_handle("Malloc pipes failed", 0);
	if (!(pids = malloc(data->nb_cmds * sizeof(pid_t))))
	{
		free(data->pipes);
		error_handle("Malloc pids failed", 0);
	}
	create_pipes(data, data->nb_cmds - 1);
	i = 0;
	while (i < data->nb_cmds)
	{
		printf("Parent process, preparing to fork child with i = %d\n", i);
		pids[i] = fork();
		if (pids[i] < 0) 	//  clean and exit
		{
			perror("Fork failed\n");
			close_pipes(data, data->nb_cmds - 1);
			free(pids);
			exit(EXIT_FAILURE);
			//free_all
			//exit
		}
		if (pids[i] == 0)
		{
			printf("Enter child process %d\n", i);
			child_process(data, i);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	wait_for_children(data, pids);
	close_pipes(data, data->nb_cmds - 1);
}

int	wait_for_children(t_shell *data, pid_t *pids)
{
	int	i;
	int	status;
	int	exit_status;
	int	last_exit_status;

	last_exit_status = EXIT_SUCCESS;
	i = 0;
	while (i < data->nb_cmds)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid failed");
			continue;  // Skip this process, but avoid infinite blocking
		}
		if (WIFEXITED(status)) // check if process exited normally (ie via exit() or return() and not via a signal)
		{
			printf("Child %d exited with status %d\n", pids[i], WEXITSTATUS(status));
			exit_status = WEXITSTATUS(status); // retrieves exit code of the process
			if (exit_status != 0)
				last_exit_status = exit_status;
		}
		else if (WIFSIGNALED(status))
			printf("Child %d was killed by signal %d\n", pids[i], WTERMSIG(status));
		else if (WIFSTOPPED(status))
			printf("Child %d was stopped by signal %d\n", pids[i], WSTOPSIG(status));
		else if (WIFCONTINUED(status))
			printf("Child %d continued execution\n", pids[i]);
		i++;
	}
	return (last_exit_status);
}

/* CHECK the WIEXITED(status)/WEXITSTATUS(status) macros, 
if it's common practice to use that or if status should be 
something stored in the data->status and passed on from 
function to function */

