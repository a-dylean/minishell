/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:05:44 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/19 16:20:39 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

	t_token	**tokens;
	// add argc checks
	tokens = (t_token **)malloc(sizeof(t_token));
	if (!tokens)
		return (1);
	*tokens = NULL;
	minishell_loop();
	if (tokens)
		free(tokens);
	// thos test encode tokens should return list of tokens
	// printf("ls | \"cat \"$ hfh\"$USER\" | \"$ $fd cat $g $\"\n");
	// tokens = encode_tokens("ls | cat \"$ hfh\" \'$USER\' | \"$ $fd cat $g $\"", tokens);
	// parser(*tokens);
    return (0);
}