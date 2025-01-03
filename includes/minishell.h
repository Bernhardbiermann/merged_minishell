/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroux <aroux@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:53:04 by aroux             #+#    #+#             */
/*   Updated: 2024/12/20 14:42:56 by aroux            ###   ########.fr       */
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
}			t_Token;

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
	t_TokenType		type; // 1912A: added that so we can build conditions on the type of redir + have the actual file it points to
	char			*filename;
	int				fd_heredoc;
}			t_redirect;

//5.12. New struct t_cmd;
typedef struct	s_cmd
{
	char		*path; // 30.11. B: think it's not necessary, can store them in the **arg
	char		**cmd;
	int			arg_count;
	int			redirect_count;
	t_redirect	*redir;
	int			input_fd;
	int			output_fd;
	//t_cmd		*next;
}			t_cmd;

typedef struct	s_shell
{
	t_cmd	*cmds;
	int		nb_cmds; // 9.12. B: I try to figure out a way with the array-approach; 
	t_env	*env;
	int		fd_hdoc;
	int		last_exit_status;
	char	*err_msg;
	int		std_in;
	int		std_out;
}			t_shell;



/* PROTOTYPES */
	/* BUILTINS */
/* __builtins.c */
int		is_builtin(t_shell *data, int i);
void	exec_builtin(t_shell *data, int i);

/* __cd.c */
void	update_pwd(t_shell *data, char *envp_key, char *envp_new_value);
void	ft_cd(t_shell *data, const char *path);

/* __echo.c */
int		check_for_option_n(char *arg);
int		ft_echo(char **args);

/* __env.c */
void	list_envp_vars(char **envp); // 18.12 A: are we using it in the end?

/* __exit.c */
int		is_a_number(char *str);
void	ft_exit(char **args, t_shell *data);

/* __export.c */
int		is_valid_var_name(const char *str);
char	*safe_malloc(t_shell *data, size_t len);
void	create_newnode_and_append(t_shell *data, char *equal_ptr, char *key);
void	expand_env(t_shell *data, char *input);
void	ft_export(char **args, t_shell *data);

/* __pwd.c */
int	ft_pwd(t_shell *data);

/* __unset.c */
t_env	*search_target_and_delete(t_env *current_input, char *key);
void	ft_unset(t_shell *data, char **args);

	/* EXECUTION */
/* __exec_cmds.c */
void	execute(t_shell *data);
void	exec_cmd(t_shell *data, int i);
void	exec_more_cmds(t_shell *data);

/* __child_process.c */
void	child_process(t_shell *data, int i, int *fd, int *prev_fd);
void	handle_redirections(t_cmd *cmd);
void	open_dup_close(t_redirect redir);
void 	redir_heredoc(t_redirect redir);

/* __find_cmd_path.c */
void	find_cmd_path(t_shell *data, int i);
char	*get_path(char **env);
char	*find_valid_path(char *cmd, char **paths);

	/* PARSING */
//LEXER
t_Token	*new_token(char *input, t_TokenType type, size_t length);
t_Token	*concatenate_token(t_Token *new_token, t_Token **token_list);
t_Token	*tokenize_input(char *input);

//LEXER_TOKEN
int		space_token(char *input, t_Token **token);
int		quote_token(char *input, t_Token **token);
int		operator_token(char *input, t_Token **token);
int		env_token(char *input, t_Token **token);
int		value_token(char *input, t_Token **token);

//LEXER_CHECK_ENV
void	find_key_and_exchange_value_in_ENV(t_env *my_envp, t_Token *current);
void	find_key_and_exchange_value_in_DQUOT(t_env *my_envp, t_Token *current, char *start);
void	three_frees(char *s1, char *s2, char *s3);
char	*compare_key_and_get_value(t_env *my_envp, char* key);
void	do_env_in_DQUOT_and_ENV(t_Token *token_list, t_env *my_envp);

//LEXER_ERROR_AND_FREE
void	free_token_list(t_Token *token_list);
void	three_frees(char *s1, char *s2, char *s3);

//LEXER_HELPER_FUNCTIONS 1-2
char	*ft_strncpy(char *src, char *start, char *end);
char	*ft_strndup(const char *s, size_t len);
char	*find_end(char* start);
char	*ft_strstr(char *big, char *little);
char	*replace_substring(char *original, char *to_replace, char *replacement);
void	replace_value(t_Token *current, char *old_key, char *value);

//LEXER_PRINT
char	*get_token_type_char(t_TokenType type);
void	print_token_list(t_Token *token_list, char* name);

//REFINE_LEXER_TOKEN 1-2
t_Token	*delete_node_and_glue(t_Token *target, t_Token **token_list);
void	delete_spaces(t_Token **token_list);
void	delete_empty_ENV_and_quote(t_Token **token_list);
void	merge_two(t_Token *current, t_Token *next);
void	merge_text_env_and_quot(t_Token **token_list);
void	check_empty_DQUOT(t_Token **token_list);
void	delete_spaces(t_Token **token_list);
void	make_text_out_of_quot(t_Token **token_list);
void	replace_special_value(t_Token *current, char *start);

//LEXER_GRAMMER_CHECK 1-2 
void	check_for_first_pipe_and_double_in_out_app_here(t_Token **token_list);
void	check_for_combination_pipe_and_in_out_app_here(t_Token **token_list);
void	check_empty_env_first(t_Token **token_list);
void	check_for_terror(t_Token **token_list);
t_Token	*des_tlist_create_syntlist(t_Token **token_list, char *value, int err);
void	check_for_pipe_in_out_app_here_last(t_Token **token_list);

//PARSER
void	parser(t_shell *data, char *input, t_env **my_envp);

//PARSER_ERROR_AND_FREE
void	free_shell(t_shell *data);
void	*safe_malloc_shell(size_t size, t_shell *data);
t_redirect	*safe_malloc_redir(size_t size, t_shell *data);

//PARSER_INITIALIZE_SHELL 1-2
int		count_cmds(t_Token **token_list);
int		count_cmd_and_arg(t_Token **token_list, int cmd_nbr);
int		count_redirect(t_Token **token_list, int cmd_nbr);
void	initialize_shell(t_shell *data, t_Token *token_list, t_env *myenvp);
void	initialize_redir(t_redirect *current, int redirect_count);
void	initialize_cmds(int cmd_c, t_shell *data);

//PARSER_PARSE_TO_SHELL
int		process_redir(t_shell *data, t_Token **current_token, int redir_c, int cmd_c);
t_Token	*setup_cmds_in_shell(t_shell *data, t_Token *current, int cmd_c);
void	fill_shell(t_shell *data, t_Token **token_list);
void	parse_to_shell(t_shell*	data, t_Token **token_list, t_env *my_envp);

//PARSER_PRINT
void	print_shell_commands(t_shell *data);

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

//INIT_AND_FREE_SHELL
void	free_shell_struct_cmds(t_shell *data, int i);
void	free_shell_struct_redir(t_shell *data, int i);
void	free_shell_struct(t_shell *data);
t_shell	*init_shell_struct(t_env *env);



/* OTHER (need to put somewhere OR just here to test the pipes */
//t_shell	*init_shell_struct(t_env *env); // 18.12 A: now in the utils
void	create_cmds(t_shell *data);		// to be removed?
void	print_cmds(t_shell *data);		// to be removed
//void	free_shell_struct(t_shell *data);	// in the utils


#endif