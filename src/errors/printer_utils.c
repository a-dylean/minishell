/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:32:04 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/14 16:35:39 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// modify with printf if no redirection (check signals and dup2)
int	syntax_error_in_token(char *token, t_shell *shell)
{
	shell->exit_status = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token '", STDERR_FILENO);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int syntax_error_eof(void)
{
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", STDERR_FILENO);
	return (1);
}

int	undefined_behavior_error(char *str)
{
	ft_putstr_fd("minishell: undefined behavior caused by ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}
