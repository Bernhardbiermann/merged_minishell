/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:17:49 by bbierman          #+#    #+#             */
/*   Updated: 2024/12/11 12:30:34 by bbierman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_token_type_char(t_TokenType type)
{
	switch (type)
	{
		case 0: return "T_ERROR";  // Example: Command
		case 1: return "T_SPACE";  // Example: Command
		case 2: return "T_S_QUOT";  // Example: Argument
		case 3: return "T_D_QUOT";  // Example: Argument
		case 4: return "T_PIPE";  // Example: Operator
		case 5: return "T_OUTPUT";  // Example: Quote
		case 6: return "T_INPUT";  // Example: Environment
		case 7: return "T_APPEND";  // Example: Operator
		case 8: return "T_HEREDOC";  // Example: Quote
		case 9: return "T_ENV";  // Example: Environment
		case 10: return "T_TEXT"; // Unknown type
	}
}

void	print_token_list(t_Token *token_list, char *name)
{
	t_Token *current = token_list;
	printf("Token List after doing: %s\n", name);
	printf("-----------------------------------------------------\n");
	printf("| %-10s | %-15s | %-6s | %-9s |\n", "Type", "Value", "Length", "Prev");
	printf("-----------------------------------------------------\n");

	while (current) {
		// Ausgabe der aktuellen Token-Informationen
		printf("| %-10s | %-15s | %-6zu | %-9p |\n",
				get_token_type_char(current->type),
				current->value ? current->value : "NULL",
				current->length,
				(void *)current->prev);
				current = current->next;
	}
	printf("-----------------------------------------------------\n");
}
