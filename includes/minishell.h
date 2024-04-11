/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:03:41 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/11 16:28:11 by atonkopi         ###   ########.fr       */
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
t_token					*encode_tokens(char *str);

/* parser */
int						parser(t_token *tokens);
t_command				*create_command(char **command, char *out, char *in,
							char *delimiter, char **env);

/* expander */

/* executer */
int						ft_terminal(void);

/* utils */
/* parser utils */
t_command	*get_last_command(t_command *head);
void	add_command_back(t_command **commands, t_command *new_node);

#endif