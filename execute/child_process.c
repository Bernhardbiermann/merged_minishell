/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:45:33 by aroux             #+#    #+#             */
/*   Updated: 2025/01/14 15:04:49 by aroux            ###   ########.fr       */
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
	handle_redirections(&data->cmds[i], fd, data, env); 
	if (data->prev_fd != -1)
	{
		if (dup2(data->prev_fd, STDIN_FILENO) == -1)
			error_handle(data, "dup2 failed: child input", EXIT_FAILURE, env);
		close_fd(data->prev_fd);
	}
	if (i != data->nb_cmds - 1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1) 
			error_handle(data, "dup2 failed: child output", EXIT_FAILURE, env);
		close_fd(fd[1]);
	}
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
	int			i;

	//if (!cmd->redir)
	//	return;
	//redir = cmd->redir;
	i = 0;
	while (i < cmd->redirect_count)
	{
		open_dup_close(cmd->redir[i], pipe, data, env);
		i++;
	}
}

void	open_dup_close(t_redir redir, int *pipe, t_shell *data, t_env **env)
{
	int	fd;

	if (redir.type == T_INPUT)
	{
		fd = open(redir.filename, O_RDONLY);
		if (!pipe)
			return ;
		check_redir(data, &redir, pipe, env); // TODO: exit status is not the right one (0 instead of 127/126, needs checking)
		//if (fd < 0)
		//	check_redir(data, &redir, pipe, env); // TODO: sort out for redundancy
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

/* check if invalid redirection (NDFD: 127, is_dir: 126) 
	and stop execution if so  */
void	check_redir(t_shell *data, t_redir *redir, int *pipe, t_env **env)
{
	DIR		*dir;

	if (access(redir->filename, F_OK) == -1)
	{
		write(2, redir->filename, ft_strlen(redir->filename));
		write(2, ": No such file or directory\n", 28);
		close_fd(data->prev_fd);
		close_fd(pipe[1]);
		close_fd(pipe[0]);
		free_shell_struct(data, env);
		exit(127);
	}
	dir = opendir(redir->filename);
	if (dir)
	{
		write(2, "utils", ft_strlen("utils"));
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

/* if heredoc, create pipe for the heredoc (suggested by chatGPT 1912A)*/
void	redir_heredoc(t_redir redir, t_shell *data, t_env **my_env)
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

