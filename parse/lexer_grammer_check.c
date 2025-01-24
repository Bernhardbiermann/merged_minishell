/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_grammer_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 09:46:14 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/24 12:27:36 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_err_in_toklst(t_shell *data, t_Token **toklst, char *val, int err)
{
	t_Token	*current;
	char	*new_value;
	char	*err_msg;

	current = *toklst;
	new_value = NULL;
	new_value = ft_strdup(val);
	err_msg = ft_strdup("minishell: syntax error near unexpected token `?'");
	data->err_msg = replace_substring(err_msg, "?", new_value);
	data->last_exit_status = err;
	current->grammer_err = 1;
	free(new_value);
	free(err_msg);
}

void	gc_check_for_combination_pipe_and_in_out_app_here(t_shell *data, \
t_Token **token_list)
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
			set_err_in_toklst(data, &current, "newline", 2);
			return ;
		}
		current = current->next;
	}
}

void	gc_check_for_first_pipe(t_shell *data, t_Token **token_list)
{
	t_Token	*current;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	if (current->type == T_PIPE)
	{
		set_err_in_toklst(data, &current, current->value, 258);
		return ;
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

void	gc_check_for_openquots(t_shell *data, t_Token **token_list)
{
	t_Token	*current;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current)
	{
		if (current->type == T_ERROR)
		{
			set_err_in_toklst(data, &current, "unclosed quotation mark", 2);
			return ;
		}
		current = current->next;
	}
}
