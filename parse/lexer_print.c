/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:17:49 by bbierman          #+#    #+#             */
/*   Updated: 2025/01/17 12:32:48 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_token_type_char(t_TokenType type)
{
	switch (type)
	{
		case 0:
			return ("T_ERROR");
		case 1:
			return ("T_SPACE");
		case 2:
			return ("T_S_QUOT");
		case 3:
			return ("T_D_QUOT");
		case 4:
			return ("T_PIPE");
		case 5:
			return ("T_OUTPUT");
		case 6:
			return ("T_INPUT");
		case 7:
			return ("T_APPEND");
		case 8:
			return ("T_HEREDOC");
		case 9:
			return ("T_ENV");
		case 10:
			return ("T_TEXT");
		default :
			return ("T_UNKNOWN");
	}
}

void	print_token_list(t_Token *token_list, char *name)
{
	t_Token	*current;

	current = token_list;
	printf("Token List after doing: %s\n", name);
	printf("-----------------------------------------------------\n");
	printf("| %-10s | %-15s | %-6s | %-9s |\n", "Type", "Value", \
	"Length", "Prev");
	printf("-----------------------------------------------------\n");
	while (current)
	{
		printf("| %-10s | %-15s | %-6zu | %-9p |\n", \
				get_token_type_char(current->type), \
				current->value ? current->value : "NULL", \
				current->length, (void *)current->prev);
		current = current->next;
	}
	printf("-----------------------------------------------------\n");
}
