/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:27:44 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/27 15:35:49 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser(t_shell *data, char *input, t_env **my_envp)
{
	t_Token	*token_list;

	token_list = tokenize_input(input);
	//print_env(*my_envp);
	//print_token_list(token_list, "tokenize");
	gc_check_for_openquots(data, &token_list);
	gc_check_for_only_empty_quotes(&token_list);
	//print_token_list(token_list, "1");
	check_empty_env_first(&token_list);
	//print_token_list(token_list, "2");
	do_env_in_dquot_and_env(token_list, *my_envp, data);
	//print_token_list(token_list, "do_env_in_dquot_and_env");
	check_empty_dquot(&token_list);
	//print_token_list(token_list, "check_empty_dquot");
	delete_empty_env_and_quote(&token_list);
	//print_token_list(token_list, "delete_empty_env_and_quote");
	merge_text_env_and_quote(&token_list);
	//print_token_list(token_list, "merge_text_env_and_quote");
	delete_spaces(&token_list);
	//print_token_list(token_list, "delete_spaces");
	gc_check_for_first_pipe(data, &token_list);
	//print_token_list(token_list, "after heredoc");
	gc_check_for_double_in_out_app_here(data, &token_list);
	gc_check_for_double_pipe(data, &token_list);
	//gc_check_for_combination_pipe_and_in_out_app_here(&token_list);
	gc_check_for_redir_last(data, &token_list);
	make_text_out_of_quot_and_env(&token_list);
	//print_token_list(token_list, "Everything!");
	data->token_list = token_list;
	do_heredoc_token(data, &token_list, my_envp);
	if (check_t_error(&token_list) != 0 || !token_list || data->sigint_hdoc == 1)
		return (1);	
	parse_to_shell(data, &token_list, *my_envp);
	//print_shell_commands(data);
	//free_token_list(token_list);
	return (0);
}
