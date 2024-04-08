/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:03:41 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/08 13:22:34 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
#include <stdio.h>

/* structures */

/* lexer */

int valid_quotes(char *str);
int get_tokens(char *str);

/* parser */

/* expander */

/* executer */
#endif