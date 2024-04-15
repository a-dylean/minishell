/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:03:41 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/15 12:02:00 by jlabonde         ###   ########.fr       */
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
}						t_info;

typedef struct s_command
{
	char				**cmd_name;
	char				*out;
	char				*in;
	char				*delimiter;
	char				**env;
	t_token				*redirections;
	struct s_command	*next;
	// add delimiter and append data if needed
	// add last or first command data if needed by pipex
}						t_command;

/* lexer */

int						valid_quotes(char *str);
t_token					*encode_tokens(char *str, t_token **tokens);

/* parser */
int						check_syntax(t_token *tokens);
int						parser(t_token *tokens);
t_command				*create_command(char **command, char *out, char *in,
							char *delimiter, char **env);
int no_pipe_in_list(t_token *tokens);

/* expander */

/* executer */
int						ft_terminal(t_token **tokens);

/* linked lists*/
t_command				*get_last_command(t_command *head);
void					add_command_back(t_command **commands,
							t_command *new_node);
t_token					*create_token(char *value, int type);
t_token					*get_last_token(t_token *head);
void					add_token_back(t_token **tokens, t_token *new_node);
void					free_stack(t_token **tokens);

/* free */
int						free_in_terminal(t_token **tokens, char *buffer);

/* errors */
int						syntax_error_in_token(char *token);
int						undefined_behavior_error(char *str);

#endif