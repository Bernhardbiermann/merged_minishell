/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:44:13 by aroux             #+#    #+#             */
/*   Updated: 2024/12/04 11:04:46 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* void	child_process(t_shell *data, int i)
{
	char	**env_tab;

	printf("Child %d redirecting stdin\n", i);
	redirect_stdin(data, data->pipes, i);
	printf("Child %d redirecting stdout\n", i);
	redirect_stdout(data, data->pipes, i);
	close_pipes(data, data->nb_cmds - 1, i);
 	if (is_builtin(data, i) == 1)
	{
		printf("Executing builtin function: %s\n", data->cmds[i]->cmd[0]);
		//builtins_functions(data->cmds->cmd_name[i], data);
		//clean and free_all
		exit(EXIT_SUCCESS);
	}
 	while (1)
	{
		find_cmd_path(data, i); // access() just needs the command path in data->cmds_path?
		env_tab = env_to_tab(data->env);
		//print_env_tab(env_tab);
		printf("Child %d executing command: %s\n", i, data->cmds[i]->path);
		if (execve(data->cmds[i]->path, data->cmds[i]->cmd, env_tab) == -1) // seems to work when tested on a smaller scale
		{
			perror("execve failed");  // If execve fails, print the error and exit
			free_tab(env_tab);
			//other frees??
			exit(EXIT_FAILURE);
        }
	 }
} */

/* if it's the 1st command (i = 0) we redirect the infile to the STDIN */
/* void	redirect_stdin(t_shell *data, int **pipes, int i)
{
	int	infile;
	
	if (i == 0)
	{
 		ADD HERE HEREDOC HANDLING
		if (data->infile->type == 2) // let's say 2 is the code for here_doc and 1 for normal doc?
			infile = open(???); // how do i open a heredoc? 
 		data->infile = strdup("test.txt");
		if (!data->infile)
		{
    		// Handle allocation failure
			printf("Malloc infile failed");
		}
		infile = open(data->infile, O_RDONLY);
		if (infile < 0)
		{
			//free_all // to be defined
			perror("Failed to open infile1");
			exit(EXIT_FAILURE); // or EXIT_STATUS?
		}
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	else // on dup2 le fd[0] to STDIN_FILENO
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup failed for STDIN");
			exit(EXIT_FAILURE);
		}
	}
} */

/* If it's the last command (i = nb_cmds - 1), we redirect the STDOUT to the output file */
/* void	redirect_stdout(t_shell *data, int **pipes, int i)
{
	int	outfile;

	if (i == data->nb_cmds - 1) // last command
	{
 		ADD HERE HEREDOC HANDLING
		if (data->outfile->type == 2) // let's say 2 is the code for here_doc and 1 for normal doc?
			outfile = open(data_heredocWHATEVER, O_WRONLY | O_CREAT | O_APPEND, 0644); // how do i open a heredoc?
 	
		// will modify this part when date->outfile is passed on by parsing. if !outfile, this function should not be executed (add a check at beggining?)
		printf("last command open outfile\n");
		outfile = open("out_test", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile < 0)
		{
			//free_all // to be defined
			perror("Failed to open outfile");
			exit(EXIT_FAILURE); // or EXIT_STATUS?
		}
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	else // on dup2 le fd[0] to STDIN_FILENO
	{
		if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
		{
			perror("dup failed for STDOUT");
			exit(EXIT_FAILURE);
		}
	}
} */
