# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbierman <bbierman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 16:33:12 by aroux             #+#    #+#              #
#    Updated: 2025/01/29 12:14:04 by bbierman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -Iincludes
LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
SRC = main.c \
	parse/lexer_check_and_print_gc.c \
	parse/lexer_check_ENV.c \
	parse/lexer_check_ENV2.c \
	parse/lexer_error_and_free.c \
	parse/lexer_grammer_check.c \
	parse/lexer_grammer_check_2.c \
	parse/lexer_hdoc_setup.c \
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
	parse/parser_mark_last_infile.c \
	parse/parser_parse_to_shell.c \
	parse/parser_print.c \
	parse/parser.c \
	utils/check_t_error.c \
	utils/env_fill.c \
	utils/env_print.c \
	utils/hdoc_expand.c \
	utils/hdoc_exec.c \
	utils/hdoc_create.c \
	utils/setup_signals.c \
	utils/setup_signals_utils.c \
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
	execute/child_process.c \
	execute/handle_redirections.c

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
