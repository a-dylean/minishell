/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:03:41 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/07 10:42:34 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define S_QUOTE '\''
# define D_QUOTE '\"'
# define PROMPT "\001\e[0m\e[35m\002minishell$> \001\e[0m\002"

extern int		g_exit_code;

/* enums */
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

typedef enum s_quotes
{
	NONE,
	DQUOTED,
	SQUOTED,
}						t_quotes;

/* structures */
typedef struct s_token
{
	int id; // check if we still use it
	int					type;
	char				*value;
	int					quotes_status;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_command
{
	char				**cmd_name;
	char *delimiter; // store the delimiter ?
	bool				is_builtin;
	t_token				*redirections;
	struct s_command	*next;
	struct s_command	*prev;
	// add delimiter and append data if needed
	// add last or first command data if needed by pipex
}						t_command;

typedef struct s_env
{
	char				*var_name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_shell
{
	char				*input;
	int					interactive;
	t_token				*tokens;
	t_command			*commands;
	int					envless;
	/*for executer below*/
	int					infile_fd;
	int					outfile_fd;
	int					prev_fd;
	pid_t				last_pid;
	int					pipe_fd[2];
	int					wstatus;
	char				*cmd_path;
	char				**env;
	/*end*/
	char				*prompt;
	char				*heredoc;
	int					exit_status;
	char				*prev_dir;
	char				*cur_dir;
	char				*user_name;
	//t_env				*env_head;
	// char			**cmd_paths;
	// char			*prev_prompt;
	// int				exec_on_pipe;
	// struct termios	mirror_termios;
	// char			*trimmed_prompt;
	// char			*terminal_prompt;
	// int				cmd_has_been_executed;
}						t_shell;

/* lexer */
int						valid_quotes(char *str);
int						lexer(t_shell *shell);
int						get_type(char *str);
int						get_type(char *str);
int						len_word(char *str, int i);
int						len_between_quotes(char *str, int i, char c);
int						count_spaces(char *str, int i);
int						len_between_tokens(char *str, int i, char c);
int						check_redir_type(char *str, int i, int count, char ch);
void					assign_type_redirections(t_token *tokens);

/* parser */
int						check_syntax(t_token *tokens);
int						parser(t_shell *shell);
int						count_tokens_before_pipe(t_token *tokens);
int						no_pipe_in_list(t_token *tokens);
void					handle_redirections(t_token *tokens, t_command *command);
void					delete_next_type(t_token **tokens, int type);
t_token					*remove_pipes(t_token *tokens, int id);

/* expander */
int						expander(t_token *tokens, t_shell *shell);
char					*get_value_after_expansion(char *token, t_shell *shell);
char					*get_value_from_buffer(char buffer[]);
int						calculate_buffer_size(char *token);
int						calculate_expansion_size(char *token, int *i);
char					*init_buffer(char *token);
char					*get_buffer_value(char *token, char *buffer,
							t_shell *shell);
void					handle_expansion(char *token, int *i, char *buffer,
							int *j);
int						calculate_buffer_size(char *token);
char					*get_env_from_str(char *str);
int						env_var_exists(char *env_var);
void					expand_to_exit_status(char *token, char *buffer, int *j,
							t_shell *shell);
void					remove_quotes(t_token *tokens);
void					perform_expansion(t_token *tokens, t_shell *shell);
void					set_quotes_status(t_token *tokens);

/* env */
t_env					*init_env(char **env);

/* executer */
int						init_shell(t_shell *shell, char **env);
int						minishell_loop(t_shell *shell);
int						non_interactive_behaviour(t_shell *shell,
							char *command);
int						executer(t_shell *shell);
void					has_no_filename(t_command *current, t_shell *shell,
							int prev_fd);
void					open_and_redirect_fd(t_command *current,
							t_shell *shell);
char					*get_cmd_path(char *cmd, t_shell *shell);
void					wait_commands(t_shell *shell);

/* heredoc */
void					handle_heredoc(t_token *redirections, t_shell *shell);

/* builtins */
int						ft_echo(t_command *commands);
int						ft_pwd(void);
int						ft_cd(t_command *commands, t_shell *shell);
void					ft_exit(t_command *commands, t_shell *shell);

/* linked lists*/
t_command				*init_command(void);
t_command				*get_last_command(t_command *head);
void					add_command_back(t_command **commands,
							t_command *new_node);
t_token					*create_token(char *value, int type, int quotes_status);
void					add_token_back(t_token **tokens, t_token *new_node);
void					free_tokens(t_token **tokens);
void					del_first(t_token **tokens);
t_token					*clear_one(t_token **tokens);
int						stack_len(t_token *tokens);
int						len_command(t_command *command);

/* errors */
int						syntax_error_in_token(char *token);
int						undefined_behavior_error(char *str);
int 					syntax_error_eof(void);

/* utils */
void					exit_shell(t_shell *shell, int exit_code);
void					free_shell(t_shell *shell);
void free_env(t_env *env);
void					free_commands(t_command **commands);
char					**init_array(int size);
void					free_array(char **arr);
int						str_is_empty_or_space_only(char *str);
int						count_chars(char *str, char c);
int						char_is_separator(char c);
void					write_error(char *cmd, char *error);

/* signals */
void					catch_sigint(int signum);

/* tests */
void					print_commands(t_command *commands);
void					test_list(t_token *tokens);
void					print_commands_reverse(t_command *commands);

#endif