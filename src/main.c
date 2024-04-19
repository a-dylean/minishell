/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:05:44 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/19 13:03:34 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

	t_token	**tokens;

	tokens = (t_token **)malloc(sizeof(t_token));
	if (!tokens)
		return (1);
	*tokens = NULL;
	ft_terminal();
	if (tokens)
		free(tokens);
	// thos test encode tokens should return list of tokens
	// printf("ls | \"cat \"$ hfh\"$USER\" | \"$ $fd cat $g $\"\n");
	// tokens = encode_tokens("ls | cat \"$ hfh\" \'$USER\' | \"$ $fd cat $g $\"", tokens);
	// parser(*tokens);
    return (0);
}