/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:32:04 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/11 14:15:00 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_error_token(char *str, char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", STDERR_FILENO);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	free(str);
	return (1);
}

int free_in_terminal(t_token **tokens, char *buffer)
{
	free_stack(tokens);
	free(buffer);
	return (EXIT_SUCCESS);
}