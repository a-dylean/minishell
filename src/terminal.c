/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:43:00 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/12 14:29:49 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_terminal(t_token **tokens)
{
	char	*buffer;

	buffer = NULL;
	while ((buffer = readline("minishell$> ")) != NULL)
	{
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
		check_syntax(*tokens);
		free_in_terminal(tokens, buffer);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
