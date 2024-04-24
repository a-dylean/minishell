/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:03:41 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/24 11:05:05 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "../pipex/pipex.h"
# include <limits.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define S_QUOTE '\''
# define D_QUOTE '\"'

/* structures */
typedef enum s_type
{
	WORD,
	PIPE,
	LESS,
	GREAT,
	GREATGREAT,
	LESSLESS,
	FILENAME,
	DELIMITER,
}						t_type;

typedef struct s_token
{
	int id; // check if we still use it
	int					type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_env
{
	char				*var_name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	struct t_command	*commands;
	int					envless;
	char				*prompt;
	char				*heredoc;
	t_env				*env_head;
	char				**env;
	int					exit_status;
	int					std_fds[2];
	char				*user_name;
	// char			**cmd_paths;
	// char			*prev_prompt;
	// int				exec_on_pipe;
	// struct termios	mirror_termios;
	// char			*trimmed_prompt;
	// char			*terminal_prompt;
	// int				cmd_has_been_executed;
}						t_shell;

typedef struct s_command
{
	char				**cmd_name;
	char				*delimiter; // store the delimiter ?
	bool				is_builtin;
	t_token				*redirections;
	struct s_command	*next;
	struct s_command	*prev;
	// add delimiter and append data if needed
	// add last or first command data if needed by pipex
}						t_command;

/* lexer */
int						valid_quotes(char *str);
int						*lexer(char *str, t_token **tokens);
int						get_type(char *str);
int						pipe_type(char *str, int i, int count);
// int						great_type(char *str, int i, int count);
// int						less_type(char *str, int i, int count);
int						get_type(char *str);
int						len_word(char *str, int i);
int						len_between_quotes(char *str, int i, char c);
int						count_spaces(char *str, int i);
int						len_between_tokens(char *str, int i, char c);
int						check_redir_type(char *str, int i, int count, char ch);
void					assign_type_redirections(t_token *tokens);

/* parser */
int						check_syntax(t_token *tokens);
int						parser(t_token *tokens, t_shell *shell);
int						count_tokens_before_pipe(t_token *tokens);
int						no_pipe_in_list(t_token *tokens);
t_token					**init_redirections(void);
void					handle_redirections(t_token *tokens, t_command *command,
							t_command **commands);
void					delete_next_type(t_token **tokens, int type);
t_token					*remove_pipes(t_token *tokens, int id);

/* expander */
int						expander(t_token *tokens, t_shell *shell);
char					*get_value_after_expansion(char *token, t_shell *shell);
int						expansion_needed(char *str, int quotes);
void					handle_expansion(char *token, int *i, char *buffer,
							int *j);
int						quotes_check(char *str);
char					*get_value_from_buffer(char buffer[]);
int						calculate_buffer_size(char *token);
int						calculate_expansion_size(char *token, int *i);
char					*init_buffer(char *token);
char					*get_buffer_value(char *token, t_shell *shell);
void					handle_expansion(char *token, int *i, char *buffer,
							int *j);
char					*get_value_from_buffer(char buffer[]);
int						calculate_buffer_size(char *token);
char					*get_env_from_str(char *str);
int						env_var_exists(char *env_var);
void					expand_to_exit_status(char *token, char *buffer, int *j,
							t_shell *shell);

/* env */
t_env					*init_env(char **env);

/* executer */
void					init_shell(t_shell *shell, char **env);
int						minishell_loop(t_shell *shell);
void					executer(t_command *commands, t_shell *shell);
t_token					*remove_pipes(t_token *tokens, int id);

/* builtins */
void					ft_echo(t_command *commands);
int						ft_pwd(void);
int						ft_cd(t_command *commands);
int						ft_exit(t_command *commands);

/* linked lists*/
t_command				*init_command(void);
t_command				*get_last_command(t_command *head);
void					add_command_back(t_command **commands,
							t_command *new_node);
t_token					*create_token(char *value, int type);
t_token					*get_last_token(t_token *head);
void					add_token_back(t_token **tokens, t_token *new_node);
void					free_tokens(t_token **tokens);
void					del_first(t_token **tokens);
t_token					*clear_one(t_token **tokens);
int						stack_len(t_token *tokens);
int						len_command(t_command *command);

/* free */
int						free_in_terminal(t_token **tokens, char *buffer);

/* errors */
int						syntax_error_in_token(char *token);
int						undefined_behavior_error(char *str);

/* utils */
char					**init_array(int size);
void					free_array(char **arr);
int						str_is_empty_or_space_only(const char *str);
int						count_chars(char *str, char c);

/* tests */
void					print_commands(t_command *commands);
void					test_list(t_token *tokens);
void					print_commands_reverse(t_command *commands);

#endif