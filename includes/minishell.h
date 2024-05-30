/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:21:38 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/30 15:22:44 by jlabonde         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define S_QUOTE '\''
# define D_QUOTE '\"'
# define PROMPT "\001\e[0m\e[35m\002minishell$> \001\e[0m\002"

extern int				g_exit_code;

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

/* structures */
typedef struct s_token
{
	int					type;
	char				*value;
	int					quotes_status;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_command
{
	char				**cmd_name;
	bool				is_builtin;
	t_token				*redirections;
	struct s_command	*next;
	struct s_command	*prev;
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
	t_token				*tokens;
	t_command			*commands;
	int					infile_fd;
	int					outfile_fd;
	pid_t				last_pid;
	int					pipe_fd[2];
	int					wstatus;
	char				*cmd_path;
	char				**env;
	char				*heredoc;
	int					old_stdin;
	int					exit_status;
	t_env				*env_list;
}						t_shell;

/* lexer */
int						valid_quotes(char *str);
int						lexer(t_shell *shell);
int						get_type(char *str);
int						len_between_tokens(char *str, int i, char c);
int						len_invalid_type(char *str);
int						check_redir_type(char *str, int i, int count, char ch);
void					assign_type_redirections(t_token *tokens);
void					set_delimiter_quote_status(t_token *token);

/* parser */
int						parser(t_shell *shell);
int						count_not_null_tokens(t_token *tokens);
void					handle_redirections(t_token *tokens,
							t_command *command);
char					**get_cmd_array_from_tokens(t_token *tokens);
bool					is_builtin(char *cmd);
t_command				*get_command(t_token *tokens);
t_token					*get_next_pipe(t_token *token);

/* expander */
char					*expander(char *str, t_shell *shell);
char					*get_value_after_expansion(char *str, t_shell *shell,
							int *i);
char					*get_new_str_value(char *str, char *old_value,
							char *new_value, int prev_index);
int						var_exists(t_env *env_head, char *var_name);
void					remove_quotes(t_token *tokens);
int						get_quote(char *str, char c);

/* env */
t_env					*init_env(char **env);
char					**init_env_array(t_env *env_head);
t_env					*init_default_env(void);
t_env					*init_env_node(char *str);
t_env					*init_default_env_node(char *var_name, char *value);
void					add_back_env_var(t_env **head, t_env *new_node);
char					*ft_getenv(t_env *env_list, char *key);
char					*get_env_value(char *str, char *var_name);
char					*get_env_from_str(char *str);
void					ft_setenv(t_env *env_head, char *name, char *value);

/* executer */
int						init_shell(t_shell *shell, char **env);
int						minishell_loop(t_shell *shell);
int						executer(t_shell *shell);
char					*get_cmd_path(char *cmd, t_shell *shell);
void					wait_commands(t_shell *shell);
void					pipe_and_fork(t_command *current, t_shell *shell);
void					close_pipe_fds(t_shell *shell);
void					handle_error(char *cmd, char *error, int exit_status,
							t_shell *shell);

/* redirections */
void					get_fds(t_token *redirections, t_shell *shell);
void					has_no_filename(t_command *current, t_shell *shell,
							int prev_fd);
void					open_and_redirect_fd(t_command *current,
							t_shell *shell);
void					get_fd_out(t_token *redirections, t_shell *shell);
void					get_fd_in(t_token *redirections, t_shell *shell);
void					close_fds(t_shell *shell);
void					duplicate_fd(int fd, int new_fd, t_shell *shell,
							int exit_status);

/* heredoc */
int						handle_heredoc(t_token *tmp, t_shell *shell,
							int option);
void					unlink_heredoc(t_shell *shell);
void					free_line(char *line, t_token *tmp);
void					write_line_to_heredoc(int fd, char *tmp, t_shell *shell,
							int quotes_status);
int						check_if_other_heredoc(t_token *current);

/* builtins */
int						ft_echo(t_command *commands);
int						ft_pwd(t_command *commands);
int						ft_cd(t_command *commands, t_shell *shell);
void					ft_exit(t_command *commands, t_shell *shell, bool pipe);
int						ft_env(t_shell *shell);
int						ft_export(char **cmd, t_shell *shell);
int						ft_unset(char **cmd, t_shell *shell);
int						is_valid_identifier(char *str);
int						free_and_return(char *curr_dir, char *old_dir, int ret);
int						handle_chdir_error(char *curr_dir, char *old_dir);

/* linked lists*/
t_command				*init_command(void);
t_command				*get_last_command(t_command *head);
void					add_command_back(t_command **commands,
							t_command *new_node);
t_token					*create_token(char *value, int type, int quotes_status);
void					add_token_back(t_token **tokens, t_token *new_node);
void					free_tokens(t_token **tokens);

/* errors */
int						check_syntax(t_token *tokens, t_shell *shell);
int						invalid_type_syntax_error(t_token *token,
							t_shell *shell);
int						syntax_error_eof(void);
int						syntax_error_in_token(char *token, t_shell *shell);
int						case_heredoc_syntax(t_token *tokens, t_shell *shell);
void					write_warning(char *arg);
int						invalid_arg(int argc);

/* utils */
void					free_and_exit_shell(t_shell *shell, int exit_code);
void					free_shell(t_shell *shell);
void					free_env(t_env *env);
void					free_commands(t_command **commands);
char					**init_array(int size);
void					free_array(char **arr);
int						str_is_empty_or_space_only(char *str);
void					write_error(char *cmd, char *error, char *arg);
char					*remove_char(char *str, char c);

/* signals */
void					catch_sigint(int signum);
void					heredoc_sigint(int signum);
void					ignore_signals(void);

#endif