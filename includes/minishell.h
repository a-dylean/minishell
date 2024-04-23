/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:03:41 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/23 14:59:27 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "../pipex/pipex.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
	int					id;
	char				*value;
	int					type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_info
{
	struct t_command	*commands;
	char				**env;
}						t_info;

typedef struct s_command
{
	char				**cmd_name;
	char				*out;
	char				*in;
	char				*delimiter;
	t_token				*redirections;
	struct s_command	*next;
	struct s_command	*prev;
	// add delimiter and append data if needed
	// add last or first command data if needed by pipex
}						t_command;

/* lexer */

int						valid_quotes(char *str);
int						*encode_tokens(char *str, t_token **tokens);
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
int						parser(t_token *tokens);
int						count_tokens_before_pipe(t_token *tokens);
int						no_pipe_in_list(t_token *tokens);
t_token					**init_redirections(void);
void					handle_redirections(t_token *tokens, t_command *command,
							t_command **commands);
void					delete_next_type(t_token **tokens, int type);

/* expander */
int						expander(t_token *tokens);
char					*get_value_after_expansion(char *token);
int						expansion_needed(char *str, int quotes);
void					handle_expansion(char *token, int *i, char *buffer,
							int *j);
int						quotes_check(char *str);
char					*get_value_from_buffer(char buffer[]);
int						calculate_buffer_size(char *token);
int						calculate_expansion_size(char *token, int *i);
char					*init_buffer(char *token);
char					*get_buffer_value(char *token);
void					handle_expansion(char *token, int *i, char *buffer,
							int *j);
char					*get_value_from_buffer(char buffer[]);
int						calculate_buffer_size(char *token);
char					*get_env_from_str(char *str);
int						env_var_exists(char *env_var);

/* executer */
int						minishell_loop(void);

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
char					*join_strings(char **strings, char *delimeter);
int						count_chars(char *str, char c);

/* tests */
void					print_commands(t_command *commands);
void					test_list(t_token *tokens);
void					print_commands_reverse(t_command *commands);
#endif