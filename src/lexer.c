/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:58:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/08 13:41:20 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int valid_quotes(char *str)
{
    int i;
    int in_single_quote = 0;
    int in_double_quote = 0;
    int result;

    i = 0;
    while(str[i])
    {
        if (str[i] == '\'')
            in_single_quote = !in_single_quote;
        else if (str[i] == '\"')
            in_double_quote = !in_double_quote;
        i++;
    }
    result = !(in_single_quote || in_double_quote);
    return result;
}

int get_tokens(char *str)
{
    int i;
    int j;
    char **tokens;

    i = 0;
    j = 0;
    //replace with split charset
    tokens = ft_split_charset(str, " \t\n");
    while (tokens[i])
    {
        printf("Token %d: %s\n", i, tokens[i]);
        i++;
    }
    return (0);
}