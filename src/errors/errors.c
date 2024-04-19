/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:32:04 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/19 14:36:55 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_error_in_token(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", STDERR_FILENO);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int	undefined_behavior_error(char *str)
{
	ft_putstr_fd("minishell: undefined behavior caused by ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

int free_in_terminal(t_token **tokens, char *buffer)
{
	(void)tokens;
	// if (tokens && *tokens)
	// 	free_tokens(tokens);
	free(buffer);
	return (EXIT_SUCCESS);
}