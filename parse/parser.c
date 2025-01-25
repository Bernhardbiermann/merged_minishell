/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:27:44 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/25 12:07:46 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser(t_shell *data, char *input, t_env **my_envp)
{
	t_Token	*token_list;

	token_list = tokenize_input(input);
	gc_check_for_openquots(data, &token_list);
	gc_check_for_only_empty_quotes(&token_list);
	check_empty_env_first(&token_list);
	do_env_in_dquot_and_env(token_list, *my_envp, data);
	check_empty_dquot(&token_list);
	delete_empty_env_and_quote(&token_list);
	merge_text_env_and_quote(&token_list);
	delete_spaces(&token_list);
	gc_check_for_first_pipe(data, &token_list);
	gc_check_for_double_in_out_app_here(data, &token_list);
	gc_check_for_double_pipe(data, &token_list);
	gc_check_for_redir_last(data, &token_list);
	make_text_out_of_quot_and_env(&token_list);
	data->token_list = token_list;
	do_heredoc_token(data, &token_list, my_envp);
	if (check_t_error(data) != 0 || !token_list)
		return (1);
	parse_to_shell(data, &token_list, *my_envp);
	return (0);
}
