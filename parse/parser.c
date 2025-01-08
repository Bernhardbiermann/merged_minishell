/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:27:44 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/08 14:50:24 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser(t_shell *data, char *input, t_env **my_envp)
{
	t_Token	*token_list;

	token_list = tokenize_input(input);
	//print_env(*my_envp);
	//print_token_list(token_list, "tokenize");
	check_for_terror(&token_list);
	check_empty_env_first(&token_list);
	do_env_in_DQUOT_and_ENV(token_list, *my_envp, data);
	//print_token_list(token_list, "do_env_in_DQUOT_and_ENV");
	check_empty_DQUOT(&token_list);
	//print_token_list(token_list, "check_empty_DQUOT");
	delete_empty_ENV_and_quote(&token_list);
	//print_token_list(token_list, "delete_empty_ENV_and_quote");
	merge_text_env_and_quote(&token_list);
	//print_token_list(token_list, "merge_text_env_and_quote");
	delete_spaces(&token_list);
	//print_token_list(token_list, "delete_spaces");
	check_for_first_pipe_and_double_in_out_app_here(&token_list);
	check_for_combination_pipe_and_in_out_app_here(&token_list);
	check_for_pipe_in_out_app_here_last(&token_list);
	make_text_out_of_quot_and_env(&token_list);
	//print_token_list(token_list, "Everything!");
	parse_to_shell(data, &token_list, *my_envp);
	//print_shell_commands(data);
	free_token_list(token_list);
}
