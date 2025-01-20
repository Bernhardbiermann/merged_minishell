# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 16:33:12 by aroux             #+#    #+#              #
#    Updated: 2025/01/17 15:36:11 by aroux            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
INCLUDES = -Iincludes
LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
SRC = main.c \
	parse/lexer_check_ENV.c \
	parse/lexer_check_ENV2.c \
	parse/lexer_create_heredoc_list.c \
	parse/lexer_error_and_free.c \
	parse/lexer_grammer_check.c \
	parse/lexer_grammer_check_2.c \
	parse/lexer_helper_functions.c \
	parse/lexer_helper_functions_2.c \
	parse/lexer_print.c \
	parse/lexer_token.c \
	parse/lexer.c \
	parse/refine_lexer_token.c \
	parse/refine_lexer_token2.c \
	parse/parser_error_and_free.c \
	parse/parser_initialize_shell.c \
	parse/parser_initialize_shell2.c \
	parse/parser_parse_to_shell.c \
	parse/parser_print.c \
	parse/parser.c \
	utils/check_t_error.c \
	utils/fill_env.c \
	utils/print_env.c \
	utils/setup_signals.c \
	utils/manip_str.c \
	utils/frees.c\
	utils/frees2.c\
	utils/shell_struct_init.c \
	utils/shell_struct_free_clean.c \
	utils/error_handle.c\
	builtins/builtins.c \
	builtins/cd.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/exit.c \
	builtins/export.c \
	builtins/export2.c \
	builtins/pwd.c \
	builtins/unset.c \
	execute/exec_cmds.c \
	execute/find_cmd_path.c \
	execute/handle_pids.c \
	execute/child_process.c\
	execute/handle_heredoc.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	
clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline_suppress.supp ./minishell

valchild:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes --suppressions=readline_suppress.supp ./$(NAME)

re: fclean all

.PHONY: all clean fclean re valgrind
