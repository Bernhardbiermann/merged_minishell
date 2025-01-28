/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:01:29 by aroux             #+#    #+#             */
/*   Updated: 2025/01/28 13:57:07 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* four types of redirection, defined at parsing stage:
- truncate >  (overwrites whatever was in the output file)
- append   >> (appends what is in the output file)
- input    <  (defines an input file that's gonna be the new end to read)
- heredoc  >> (creates file delimitated by an EOF mark, that user can append)*/
void	handle_redirections(t_cmd *cmd, int *pipe, t_shell *data, t_env **env)
{
	int	i;

	if (!cmd->redir)
		return ;
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
			fd = open(redir.filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(redir.filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			error_handle(data, "Failed to open output file", 1, env);
		if (dup2(fd, STDOUT_FILENO) == -1)
			error_handle(data, "dup2 failed for output redirection", 1, env);
		close(fd);
	}
	else if (redir.type == T_INPUT || redir.type == T_HEREDOC)
	{
		fd = open(redir.filename, O_RDONLY);
		if (pipe)
			check_redir(data, &redir, pipe, env);
		if (fd < 0)
			error_handle(data, "file failed to open", 1, env);
		if (dup2(fd, STDIN_FILENO) == -1)
			error_handle(data, "dup2 failed for input redirection", 1, env);
		close(fd);
	}
}

/* check if invalid redirection (NDFD: 127, is_dir: 126) 
	and stop execution if so  */
void	check_redir(t_shell *data, t_redir *redir, int *pipe, t_env **env)
{
	DIR		*dir;

	if (redir->type == T_INPUT && access(redir->filename, F_OK) == -1)
	{
		write(2, redir->filename, ft_strlen(redir->filename));
		write(2, ": No such file or directory\n", 28);
		close_fd(data->prev_fd);
		close_fd(pipe[1]);
		close_fd(pipe[0]);
		free_shell_struct(data, env);
		exit(1);
	}
	dir = opendir(redir->filename);
	if (dir)
	{
		write(2, redir->filename, ft_strlen(redir->filename));
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

void	handle_redirections_builtin(t_cmd *cmd, t_shell *data, t_env **env)
{
	int	i;

	if (!cmd->redir)
		return ;
	i = 0;
	while (i < cmd->redirect_count)
	{
		open_dup_close_builtin(cmd->redir[i], data, env);
		if (cmd->redir[i].type == T_OUTPUT || cmd->redir[i].type == T_APPEND)
			cmd->output_fd = 1;
		i++;
	}
}

void	open_dup_close_builtin(t_redir redir, t_shell *data, t_env **env)
{
	int	fd;

	if (redir.type == T_OUTPUT || redir.type == T_APPEND)
	{
		if (redir.type == T_OUTPUT)
			fd = open(redir.filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(redir.filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			error_handle(data, "Failed to open output file", 1, env);
/* 		if (dup2(fd, STDOUT_FILENO) == -1)
			error_handle(data, "dup2 failed for output redirection", 1, env); */
		close(fd);
	}
	else if (redir.type == T_INPUT || redir.type == T_HEREDOC)
	{
		fd = open(redir.filename, O_RDONLY);
		if (fd < 0)
			error_handle(data, "file failed to open", 1, env);
/* 		if (dup2(fd, STDIN_FILENO) == -1)
			error_handle(data, "dup2 failed for input redirection", 1, env); */
		close(fd);
	}
}
