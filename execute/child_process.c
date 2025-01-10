/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:45:33 by aroux             #+#    #+#             */
/*   Updated: 2025/01/10 11:47:17 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(t_shell *data, int i, int *fd, t_env **my_env)
{
	handle_redirections(&data->cmds[i], fd, data, my_env); 
	if (data->prev_fd != -1) // If there's a previous pipe, read from it
	{
		//printf("Child %d dup2: prev_fd=%d, fd[1]=%d\n", i, data->prev_fd, fd[1]);
		if (dup2(data->prev_fd, STDIN_FILENO) == -1)
			error_handle(data, "dup2 failed: child input", EXIT_FAILURE, my_env);
		close_fd(data->prev_fd); // Close after duplicating
	}
	if (i != data->nb_cmds - 1) // If not last command, write to the current pipe
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1) 
			error_handle(data, "dup2 failed: child output", EXIT_FAILURE, my_env);
		close_fd(fd[1]);
	}
	//if (i == data->nb_cmds - 1)
	//	exec_last_cmd(data, my_env); // TODO
//	if (i != 0)
//		close(fd[0]);
	close_fd(fd[1]);       // Close current pipe's write end
	close_fd(fd[0]);
	//check_invalid_redir(data, i, my_env);// TODO check if invalid redirection (no such file or directory 127 OR is directory 126) and stop execution if so 
	exec_cmd(data, i, my_env);
}


/* four types of redirection, defined at parsing stage:
- truncate  >  (overwrites whatever was in the output file)
- append    >> (appends what is in the output file)
- input 	<  (defines an input file that's gonna be the new end to read)
- heredoc	>> (creates a file delimitated by an EOF mark, that the user can append)
How Fabbio and his partner handled it: if they have a list of token, they check token->type = COMMAND, 
and if token->next->type = redirection (trunc, append, input or heredoc), then we redirect the fd_in or the fd_out
 */
void	handle_redirections(t_cmd *cmd, int *pipe, t_shell *data, t_env **env)
{
	//t_redirect	*redir;
	int			i;

	//if (!cmd->redir)
	//	return;
	//redir = cmd->redir;
	i = 0;
	while (i < cmd->redirect_count) // 1912A: seems that Nick handled multiple redir by just having a linked list of redirection and using here a while loop
	{
		open_dup_close(cmd->redir[i], pipe, data, env);
		i++;
	}
}

void	open_dup_close(t_redirect redir, int *pipe, t_shell *data, t_env **env)
{
	int	fd;

	if (redir.type == T_INPUT) // input file
	{
		fd = open(redir.filename, O_RDONLY);
		if (fd < 0)
			check_redir(data, &redir, pipe, env);
		if (dup2(fd, STDIN_FILENO) == -1)
			error_handle(data, "dup2 failed for input redirection", 1, env);
		close_fd(fd);
	}
	else if (redir.type == T_OUTPUT || redir.type == T_APPEND)
	{
		if (redir.type == T_OUTPUT)
			fd = open(redir.filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(redir.filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			error_handle(data, "Failed to open output file", 1, env);
		if (dup2(fd, STDOUT_FILENO) == -1)
			error_handle(data, "dup2 failed for output redirection", 1, env);
		close_fd(fd);
	}
	//else if (redir.type == T_HEREDOC)
	//	redir_heredoc(redir, ddata, my_env);
}

/* check if invalid redirection (no such file or directory 127 OR is directory 126) and stop execution if so  */
void	check_redir(t_shell *data, t_redirect *redir, int *pipe, t_env **env)
{
	int		last_exit_status;
	DIR		*dir;

	if (access(redir->filename, F_OK) == -1)
	{
		write(2, redir->filename, ft_strlen(redir->filename));
		write(2, ": No such file or directory\n", ft_strlen(": No such file or directory\n"));
		close_fd(data->prev_fd);
		close_fd(pipe[1]);
		close_fd(pipe[0]);      // Close current pipe's write end
		free_shell_struct(data, env);
		if (env)  // 10.01: to remove eventually, just here for compilation when using clean_shell_struct
			last_exit_status = 127;
		//free_env_list(my_env, NULL, NULL);
		last_exit_status = 127;  // maybe even not necessary: directly put the value in exit
		exit(last_exit_status) ;

	}
	dir = opendir(redir->filename);
	if (dir) // check right syntax but here check if a directory
	{
		write(2, redir->filename, ft_strlen(redir->filename));
		write(2, ": Is a directory\n", ft_strlen(": Is a directory\n"));
		closedir(dir);
		close_fd(data->prev_fd);
		close_fd(pipe[1]);
		close_fd(pipe[0]);
		free_shell_struct(data, env);
		if (env)  // 10.01: to remove eventually, just here for compilation when using clean_shell_struct
			last_exit_status = 126;
		//free_env_list(my_env, NULL, NULL);
		last_exit_status = 126; // maybe even not necessary
		exit(last_exit_status) ;
	}
	return ;
}

/* if heredoc, create pipe for the heredoc (suggested by chatGPT 1912A)*/
void redir_heredoc(t_redirect redir, t_shell *data, t_env **my_env)
{
	int	fd[2];

	if (pipe(fd) == -1)
		error_handle(data, "pipe failed for heredoc", EXIT_FAILURE, my_env);
	write(fd[1], redir.filename, 50); // 1912A: to adapt to what is effectively our heredoc form and content
	close_fd(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error_handle(data, "dup2 failed for heredoc", EXIT_FAILURE, my_env);
	close_fd(fd[0]);
}

