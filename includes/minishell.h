/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:03:41 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/08 16:29:55 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>

/* structures */

typedef struct s_token
{
    char    *value;
    int     type;
}   t_token;

typedef struct s_command
{
    char	*path;
	char	**command;
	char	**env;
    char	*outfile_name;
	char	*infile_name;
}   t_command;
	
/* lexer */

int valid_quotes(char *str);
int get_tokens(char *str);

/* parser */

/* expander */

/* executer */
int	ft_terminal();
#endif