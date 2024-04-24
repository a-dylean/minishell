/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:43:00 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/24 15:33:40 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	trim_and_verify_buffer(char *buffer)
{
	buffer = ft_strtrim(buffer, " ");
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		return (1);
	}
	else if (!valid_quotes(buffer))
	{
		printf("Error: invalid quotes\n");
		free(buffer);
		return (1);
	}
	else if (buffer[0] != '\0')
			add_history(buffer);
	return (0);
}

int	minishell_loop(t_shell *shell)
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
		if (trim_and_verify_buffer(buffer) == 1)
			continue ;
		lexer(buffer, tokens);
		if (!check_syntax(*tokens))
			parser(*tokens, shell);
		//free_in_terminal(tokens, buffer);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
