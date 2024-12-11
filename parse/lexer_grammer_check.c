/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_grammer_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:46:14 by bbierman          #+#    #+#             */
/*   Updated: 2024/12/11 12:29:54 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_Token	*des_tlist_create_syntlist(t_Token **token_list, char *value, int err)
{
	t_Token	*new_token_list;
	char	*replaced_msg;
	char	*new_value;
	char	*err_msg;

	new_token_list = NULL;
	new_value = ft_strdup(value);
	err_msg = ft_strdup("minishell: syntax error near unexpected token `?'");
	free_token_list(*token_list);
	replaced_msg = replace_substring(err_msg, "?", new_value);
	new_token_list = new_token(ft_strdup(replaced_msg), T_ERROR, err);
	three_frees(replaced_msg, err_msg, new_value);
	return (new_token_list);
}

void	check_for_combination_pipe_and_in_out_app_here(t_Token **token_list)
{
	t_Token	*current;
	t_Token	*next;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current && current->next)
	{
		next = current->next;
		if ((current->type == T_PIPE) && \
		(next->type == T_INPUT || next->type == T_OUTPUT || \
		next->type == T_APPEND || next->type == T_HEREDOC))
		{
			*token_list = des_tlist_create_syntlist(token_list, "newline", 2);
			return ;
		}
		current = current->next;
	}
}

void	check_for_first_pipe_and_double_in_out_app_here(t_Token **token_list)
{
	t_Token	*current;
	t_Token	*next;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	if (current->type == T_PIPE)
	{
		*token_list = des_tlist_create_syntlist(token_list, current->value, 258);
		return ;
	}
	while (current && current->next)
	{
		next = current->next;
		if ((current->type == T_INPUT || current->type == T_OUTPUT || \
		current->type == T_APPEND || current->type == T_HEREDOC) && \
		(next->type == T_INPUT || next->type == T_OUTPUT || next->type == \
		T_APPEND || next->type == T_HEREDOC || next->type == T_PIPE))
		{
			*token_list = des_tlist_create_syntlist(token_list, next->value, 2);
			return ;
		}
		current = current->next;
	}
}

void	check_empty_env_first(t_Token **token_list)
{
	t_Token	*current;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current)
	{
		if (current->type == T_ENV && current->value[0] == '\0')
		{
			free(current->value);
			current->value = ft_strdup("$");
			current->type = T_TEXT;
			current->length = ft_strlen(current->value);
		}
		current = current->next;
	}
}

void	check_for_terror(t_Token **token_list)
{
	t_Token	*current;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current)
	{
		if (current->type == T_ERROR)
		{
			*token_list = des_tlist_create_syntlist(token_list, \
"unclosed quotation mark", 2);
			return ;
		}
		current = current->next;
	}
}

