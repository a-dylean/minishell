/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:19:54 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/30 15:15:46 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_error_in_token(char *token, t_shell *shell)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	shell->exit_status = 2;
	return (1);
}

int	syntax_error_eof(void)
{
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n",
		STDERR_FILENO);
	return (1);
}

void	write_error(char *cmd, char *error, char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putchar_fd('`', STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putchar_fd('\'', STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	write_warning(char *arg)
{
	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited by end-of-file (wanted `",
		STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("\')\n", STDERR_FILENO);
}

int	invalid_arg(int argc)
{
	if (argc != 1)
		return (write_error(NULL, "minishell doesn't take any arguments", NULL),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
