/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:43:00 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/19 11:53:25 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_terminal()
{
	char	*buffer;
	t_token	**tokens;

	buffer = NULL;
	while ((buffer = readline("minishell$> ")) != NULL)
	{
		tokens = (t_token **)malloc(sizeof(t_token));
		if (!tokens)
			return (1);
		*tokens = NULL;
		buffer = ft_strtrim(buffer, " ");
		if (!valid_quotes(buffer))
		{
			printf("Error: invalid quotes\n");
			free_in_terminal(tokens, buffer);
			continue ;
		}
		if (ft_strncmp(buffer, "exit", 4) == 0)
		{
			free_in_terminal(tokens, buffer);
			break ;
		}
		if (buffer[0] != '\0')
			add_history(buffer);
		encode_tokens(buffer, tokens);
		if (!check_syntax(*tokens))
			parser(*tokens);
		free_in_terminal(tokens, buffer);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
