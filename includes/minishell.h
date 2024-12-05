/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:53:04 by aroux             #+#    #+#             */
/*   Updated: 2024/12/05 16:45:26 by aroux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

/* LIBRARIES */
# include <unistd.h> 	// fork(), pipe(), dup2(), execve(), close()
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>	// getwd()
# include <fcntl.h>		// O_WRONLY and O_CREAT files
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>	// to use the pid_t type
# include <sys/wait.h>	// wait()
# include <sysexits.h>	// exit processes?
# include "libft/include/libft.h"
# include "libft/include/ft_printf.h"
# include "libft/include/get_next_line.h"

/* MACROS */

/* STRUCTURES */
// PARSE_LEXER
typedef enum s_t_TokenType
{
	T_ERROR = 0,
	T_SPACE = 1,
	T_S_QUOT = 2,
	T_D_QUOT = 3,
	T_PIPE = 4,
	T_OUTPUT = 5,
	T_INPUT = 6,
	T_APPEND = 7,
	T_HEREDOC = 8,
	T_ENV = 9,
	T_TEXT = 10
}			t_TokenType;

typedef struct s_token
{
	t_TokenType		type;
	char			*value;
	size_t			length;
	struct s_token	*next;
	struct s_token	*prev;
}			Token;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
	int					size; // relevant??
}			t_env;

/* 2.12: newly added struct */
typedef struct s_redirect
{
	char			*infile;
	char			*trunc;
	char			*append;
}			t_redirect;

//5.12. New struct t_cmd;
typedef struct	s_cmd
{
	char		*path; // 30.11. B: think it's not necessary, can store them in the **arg
	char		**cmd;
	int			arg_count;
	int			redirect_count;
	t_redirect	*redir; // 30.11. B: need a 2-dimensional redirect, there can be more than one

}			t_cmd;

typedef struct	s_shell
{
	t_cmd	**cmds; // 5.12, A: in the end I left the **, because some functions only work with pointer and not t_cmd struct themselves. If you manage to make it work without the code exploding to your face, go for it ^^'
	int		nb_cmds;
	t_env	*env;
	int		fd_hdoc;
	char	**hdoc_delim;
	int		last_exit_status;
	char	*err_msg;
}			t_shell;



/* PROTOTYPES */
/* BUILTINS */

/* __builtins.c */
int	is_builtin(t_shell *data, int i);

/* EXECUTE */
/* __execute.c */	// 5.12, A: this file is obsolete for now
/* void	exec_cmd(t_shell *data);
void	exec_one_cmd(t_shell *data);
void	exec_more_cmds(t_shell *data);
int		wait_for_children(t_shell *data, pid_t *pids); */

/* __exec_cmds.c */
void	execute(t_shell *data);
void	exec_more_cmds(t_shell *data);
void	child_process(t_shell *data, int i, int *fd, int *prev_fd);
void	exec_cmd(t_shell *data, int i);

/* __pipes.c */  		 // 5.12, A: this file is obsolete for now
/* void	create_pipes(t_shell *data, int nb_pipes);
void	close_pipes(t_shell *data, int nb_pipes, int index_process); */

/* __child_process.c */ // 5.12, A: this file is obsolete for now
/* void	child_process(t_shell *data, int i);
void	redirect_stdin(t_shell *data, int **pipes, int i);
void	redirect_stdout(t_shell *data, int **pipes, int i); */

/* __find_cmd_path.c */
void	find_cmd_path(t_shell *data, int i);
char	*get_path(char **env);
char	*find_valid_path(char *cmd, char **paths);

/* PARSE */
//LEXER
Token	*new_token(char *input, t_TokenType type, size_t length);
Token	*concatenate_token(Token *new_token, Token **token_list);
Token	*tokenize_input(char *input);

//LEXER_TOKEN
int		space_token(char *input, Token **token);
int		quote_token(char *input, Token **token);
int		operator_token(char *input, Token **token);
int		env_token(char *input, Token **token);
int		value_token(char *input, Token **token);

//LEXER_CHECK_ENV
void	find_key_and_exchange_value_in_ENV(t_env *my_envp, Token *current);
void	find_key_and_exchange_value_in_DQUOT(t_env *my_envp, Token *current, char *start);
void	three_frees(char *s1, char *s2, char *s3);
char	*compare_key_and_get_value(t_env *my_envp, char* key);
void	do_env_in_DQUOT_and_ENV(Token *token_list, t_env *my_envp);

//LEXER_ERROR_AND_FREE
void	free_token_list(Token *token_list);
void	three_frees(char *s1, char *s2, char *s3);

//LEXER_HELPER_FUNCTIONS 1-2
char	*ft_strncpy(char *src, char *start, char *end);
char	*ft_strndup(const char *s, size_t len);
char	*find_end(char* start);
char	*ft_strstr(char *big, char *little);
char	*replace_substring(char *original, char *to_replace, char *replacement);
void	replace_value(Token *current, char *old_key, char *value);

//LEXER_PRINT
char	*get_token_type_char(t_TokenType type);
void	print_token_list(Token *token_list, char* name);

//REFINE_LEXER_TOKEN 1-2
Token	*delete_node_and_glue(Token *target, Token **token_list);
void	delete_spaces(Token **token_list);
void	delete_empty_ENV_and_quote(Token **token_list);
void	merge_two(Token *current, Token *next);
void	merge_text_env_and_quot(Token **token_list);
void	check_empty_DQUOT(Token **token_list);
void	delete_spaces(Token **token_list);
void	make_text_out_of_quot(Token **token_list);
void	replace_special_value(Token *current, char *start);

//GRAMMER_CHECK
void	check_for_first_pipe_and_double_in_out_app_here(Token **token_list);
void	check_for_combination_pipe_and_in_out_app_here(Token **token_list);
void	check_empty_env_first(Token **token_list);
void	check_for_terror(Token **token_list);
Token	*des_tlist_create_syntaxelist(Token **token_list, char *value, int err);

//PARSER
void	parser(char *input, t_env **my_envp);

//PARSER_ERROR_AND_FREE
void	free_shell(t_shell *data);
void	*safe_malloc_shell(size_t size, t_shell *data);

//PARSER_INITIALIZE_SHELL
int	count_cmds(Token **token_list);
int	count_cmd_and_arg(Token **token_list, int cmd_nbr);
int	count_redirect(Token **token_list, int cmd_nbr);
void	initialize_shell(t_shell *data, Token *token_list, t_env *myenvp);


/* UTILS */
/* __fill_env.c */
t_env	*create_env_node(char *key, char *value);
void	append_to_lst(t_env **lst, t_env *new);
t_env	*fill_env_node(char *env_var, t_env **my_envp);
t_env	**create_myenvp(char **envp);
void	free_env_list(t_env **my_envp, char *key, char *value);

/* __print_env.c */
int		env_size(t_env *lst);
char	**env_to_tab(t_env *env);
void	print_env(t_env *env);
void	print_env_tab(char **tab);
//t_env	**sort_env(t_env **env, int env_len);

/* __manip_str.c */
char	*multi_strjoin(char *str1, char *str2, char *str3);
int		is_empty_str(char *str);

/* __error_handle.c */
void	error_handle(char *error_msg, int err_code);

/* __frees.c */
void	free_tab(char **tab);
void	free_many_splits(char **split1, char **split2);
void	free_cmds_close_files(int i, char ***cmds, int infile, int outfile);
void	multi_close(int fds[], int size, int infile, int outfile);

/* OTHER (need to put somewhere OR just here to test the pipes */
t_shell	*init_shell_struct(t_env *env);
void	create_cmds(t_shell *data);
void	print_cmds(t_shell *data);
void	free_shell_struct(t_shell *data);

#endif