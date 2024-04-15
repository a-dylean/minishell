/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:05:44 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/15 12:15:25 by jlabonde         ###   ########.fr       */
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
	ft_terminal(tokens);
	if (tokens)
		free(tokens);
	// *tokens = encode_tokens("ls -l -h hfjg << file1 | cat -ls >> hello | popo", tokens);
	// parser(*tokens);
    return (0);
}