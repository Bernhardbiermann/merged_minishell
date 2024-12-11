/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:20:42 by bbierman          #+#    #+#             */
/*   Updated: 2024/12/11 12:30:58 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	space_token(char *input, t_Token **token)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	*token = new_token(ft_strndup(input, i), T_SPACE, i);
	return (i);
}

int	quote_token(char *input, t_Token **token)
{
	int	i;

	i = 1;
	while (input[i] && input[i] != input[0])
		i++;
	if (input[i] == input[0])
	{
		if (input[0] == '\'')
			*token = new_token(ft_strndup(input + 1, i - 1), T_S_QUOT , (i - 1));
		else
			*token = new_token(ft_strndup(input + 1, i - 1), T_D_QUOT , (i - 1));
		return (i + 1);
	}
	else
	{
		*token = \
new_token(ft_strdup("minishell: Unclosed quotation marks detected"), \
T_ERROR , 1);
		return (i);
	}
}

int	operator_token(char *input, t_Token **token)
{
	if ((input[0] == '>' && input[1] == '>') || \
	(input[0] == '<' && input[1] == '<'))
	{
		if (input[0] == '>')
			*token = new_token(ft_strndup(input, 2), T_APPEND, 2);
		else
			*token = new_token(ft_strndup(input, 2), T_HEREDOC, 2);
		return (2);
	}
	else
	{
		if (input[0] == '|')
			*token = new_token(ft_strndup(input, 1), T_PIPE, 1);
		else if (input[0] == '>')
			*token = new_token(ft_strndup(input, 1), T_INPUT, 1);
		else
			*token = new_token(ft_strndup(input, 1), T_OUTPUT, 1);
		return (1);
	}
}

int	env_token(char *input, t_Token **token)
{
	int	i;

	i = 1;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	*token = new_token(ft_strndup(input + 1, i - 1), T_ENV, (i - 1));
	return (i);
}

int	value_token(char *input, t_Token **token)
{
	int	i;

	i = 0;
	while (input[i] && !ft_strchr(" |<>\"'$", input[i]))
		i++;
	*token = new_token(ft_strndup(input, i), T_TEXT, i);
	return (i);
}
