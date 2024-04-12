/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:03:41 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/11 14:15:35 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "../pipex/pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>

#define S_QUOTE '\''
#define D_QUOTE '\"'

/* structures */

// typedef	enum s_quotes
// {
// 	S_QUOTE,
// 	D_QUOTE,
// 	UNQUOTE,
// }	t_quotes;

typedef struct s_total
{
	struct s_token	*tokens;
}	t_total;

typedef enum s_type
{
	WORD,
	PIPE,
	LESS,
	GREAT,
	GREATGREAT,
	LESSLESS,
}	t_type;

typedef struct s_token
{
    char    *value;
    int		type;
	struct s_token	*next;
}   t_token;

typedef struct s_command
{
	char	**command;
    char	*out;
	char	*in;
	char	*delimiter;
	char	**env;	
	// add delimiter and append data if needed
	// add last or first command data if needed by pipex
}   t_command;
	
/* lexer */

int valid_quotes(char *str);
t_token	*encode_tokens(char *str, t_token **tokens);


/* parser */

/* expander */

/* executer */
int	ft_terminal(t_token **tokens);

/* linked lists*/
t_token	*create_token(char *value, int type);
t_token	*ft_get_last_node(t_token *head);
void	ft_add_node_back(t_token **tokens, t_token *new_node);
void	free_stack(t_token **tokens);

/* free */
int free_in_terminal(t_token **tokens, char *buffer);

#endif