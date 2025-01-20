/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:45:33 by aroux             #+#    #+#             */
/*   Updated: 2025/01/20 12:41:51 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* the child process:
	- checks and handles redirections 	
	- duplicates prev_fd to STDIN and closes it (if there is a prev_fd)
	- duplicates write end of pipe to STDOUT if not the last cmd and closes it
	- closes all remaining files descriptors
	- executes the command */
void	child_process(t_shell *data, int i, int *fd, t_env **env)
{
	int	saved_stdout;

	data->cmds[i].output_fd = -1; // TODO: 1401A - added to fix echo |echo, add to the merge if it works
	if (data->prev_fd != -1)
	{
		if (dup2(data->prev_fd, STDIN_FILENO) == -1)
			error_handle(data, "dup2 failed: child input", EXIT_FAILURE, env);
		close_fd(data->prev_fd);
	}
	// TODO: 1401A suggested by chatgpt but doesnt seem to fix the code
	if (i != data->nb_cmds - 1)
	{
		// 1401a, 18:49: added all this to try and solve echo >out | echo >out
		// TODO: add to merged version if works
		if (data->cmds[i].output_fd != -1)
		{
			saved_stdout = dup(STDOUT_FILENO);
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				error_handle(data, "dup2 failed: outfile", EXIT_FAILURE, env);
			if (dup2(saved_stdout, STDOUT_FILENO) == -1)
				error_handle(data, "dup2 failed: restore STDOUT", EXIT_FAILURE, env);
			close_fd(saved_stdout);
		}
		else
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1) 
				error_handle(data, "dup2 failed: child output", EXIT_FAILURE, env);
		}
		close_fd(fd[1]);
	}
	else // last command
	{
		if (data->cmds[i].output_fd != -1) 
		{
			// If we have output redirection, send it to file
			if (dup2(data->cmds[i].output_fd, STDOUT_FILENO) == -1)
				error_handle(data, "dup2 failed: last command output redirection", EXIT_FAILURE, env);
		}
	}
	handle_redirections(&data->cmds[i], fd, data, env);
	close_fd(fd[1]);
	close_fd(fd[0]);
	exec_cmd(data, i, env);
}


/* four types of redirection, defined at parsing stage:
- truncate >  (overwrites whatever was in the output file)
- append   >> (appends what is in the output file)
- input    <  (defines an input file that's gonna be the new end to read)
- heredoc  >> (creates file delimitated by an EOF mark, that user can append)*/
void	handle_redirections(t_cmd *cmd, int *pipe, t_shell *data, t_env **env)
{
	//t_redir	*redir;
	int	i;

	if (!cmd->redir)
		return ;
	//redir = cmd->redir;
	i = 0;
	while (i < cmd->redirect_count)
	{
		open_dup_close(cmd->redir[i], pipe, data, env);
		if (cmd->redir[i].type == T_OUTPUT || cmd->redir[i].type == T_APPEND)
			cmd->output_fd = 1;
		i++;
	}
}

void	open_dup_close(t_redir redir, int *pipe, t_shell *data, t_env **env)
{
	int	fd;

	if (redir.type == T_OUTPUT || redir.type == T_APPEND)
	{
		if (redir.type == T_OUTPUT)
			fd = open(redir.redir_arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(redir.redir_arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
		// TODO: check redir to check if its a directory and if i have not the permissions to open the file(?)
		// check_redir(data, &redir, pipe, env);
		if (fd < 0)
			error_handle(data, "Failed to open output file", 1, env);
		if (dup2(fd, STDOUT_FILENO) == -1)
			error_handle(data, "dup2 failed for output redirection", 1, env);
		close(fd);
	}
	else if (redir.type == T_INPUT)
	{
		fd = open(redir.redir_arg, O_RDONLY);
		check_redir(data, &redir, pipe, env); // TODO: exit status is not the right one (0 instead of 127/126, needs checking)
		if (fd < 0)
			error_handle(data, "file failed to open", 1, env);
		if (dup2(fd, STDIN_FILENO) == -1)
			error_handle(data, "dup2 failed for input redirection", 1, env);
		close(fd);
	}
	else if (redir.type == T_HEREDOC)
		redir_heredoc(redir, data, env);
}

/* check if invalid redirection (NDFD: 127, is_dir: 126) 
	and stop execution if so  */
void	check_redir(t_shell *data, t_redir *redir, int *pipe, t_env **env)
{
	DIR		*dir;

	if (redir->type == T_INPUT && access(redir->redir_arg, F_OK) == -1)
	{
		write(2, redir->redir_arg, ft_strlen(redir->redir_arg));
		write(2, ": No such file or directory\n", 28);
		close_fd(data->prev_fd);
		close_fd(pipe[1]);
		close_fd(pipe[0]);
		free_shell_struct(data, env);
		exit(1);
	}
	dir = opendir(redir->redir_arg);
	if (dir)
	{
		write(2, redir->redir_arg, ft_strlen(redir->redir_arg));
		write(2, ": Is a directory\n", ft_strlen(": Is a directory\n"));
		closedir(dir);
		close_fd(data->prev_fd);
		close_fd(pipe[1]);
		close_fd(pipe[0]);
		free_shell_struct(data, env);
		exit(126);
	}
	return ;
}
// 1701A: check the logic, not sure it works as it is
void	redir_heredoc(t_redir redir, t_shell *data, t_env **env)
{
	if (redir.last_redir == 0) // if not the last heredoc we just execute it but we don't plug it to the rest of the execution
	{
		exec_heredoc(data, redir.redir_arg, env);
		close_fd(data->fd_heredoc);
	}
	else
	{
		exec_heredoc(data, redir.redir_arg, env);
		if (dup2(data->fd_heredoc, STDIN_FILENO) == -1)
			error_handle(data, "dup2 failed for input redirection", 1, env);
		close_fd(data->fd_heredoc);
	}
}

