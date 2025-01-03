# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 16:33:12 by aroux             #+#    #+#              #
#    Updated: 2024/12/20 10:29:48 by bbierman         ###   ########.fr        #
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
	utils/fill_env.c \
	utils/print_env.c \
	utils/manip_str.c \
	utils/frees.c\
	utils/init_and_free_shell.c \
	utils/error_handle.c\
	builtins/builtins.c \
	builtins/cd.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/exit.c \
	builtins/export.c \
	builtins/pwd.c \
	builtins/unset.c \
	execute/exec_cmds.c \
	execute/find_cmd_path.c \
	execute/child_process.c

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
	/usr/local/bin/valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline_suppress.supp ./minishell

valchild:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes ./$(NAME)

re: fclean all

.PHONY: all clean fclean re valgrind
