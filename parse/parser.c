/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:27:44 by bbierman          #+#    #+#             */
/*   Updated: 2024/11/29 11:05:04 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser(char *input, t_env **my_envp)
{
	Token	*token_list;

	token_list = tokenize_input(input);
	print_env(*my_envp);
	print_token_list(token_list, "tokenize");
	check_for_terror(&token_list);
	do_env_in_DQUOT_and_ENV(token_list, *my_envp);
	check_empty_env_first(&token_list);
	print_token_list(token_list, "do_env_in_DQUOT_and_ENV");
	check_empty_DQUOT(&token_list);
	//print_token_list(token_list, "check_empty_DQUOT");
	delete_empty_ENV_and_quote(&token_list);
	//print_token_list(token_list, "delete_empty_ENV_and_quote");
	merge_text_env_and_quot(&token_list);
	//print_token_list(token_list, "merge_text_env_and_quot");
	delete_spaces(&token_list);
	check_for_first_pipe_and_double_in_out_app_here(&token_list);
	check_for_combination_pipe_and_in_out_app_here(&token_list);
	make_text_out_of_quot(&token_list);
	//print_token_list(token_list, "Everything!");
	free_token_list(token_list);
}
