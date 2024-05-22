/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:43:34 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/07 17:33:48 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	compute_exit_status(long stat, t_shell *shell, bool pipe)
{
	if (stat > 255)
		stat = stat % 256;
	else if (stat < 0)
		stat = (stat % 256) + 256;
	if (pipe == false)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	shell->exit_status = stat;
}

static int	get_exit_status(t_command *commands, char *arg, t_shell *shell, bool pipe)
{
	long stat;

	stat = ft_atol(arg);
	if (errno == ERANGE)
	{
		if (pipe == false)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("exit: ", STDOUT_FILENO);
		ft_putstr_fd(arg, STDOUT_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDOUT_FILENO);
		shell->exit_status = 2;
	}
	else if (commands->cmd_name[1] && commands->cmd_name[2])
	{
		if (pipe == false)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		write_error("exit", "too many arguments");
		shell->exit_status = 1;
		return (1);
	}
	else
		compute_exit_status(stat, shell, pipe);
	return (0);
}

void	ft_exit(t_command *commands, t_shell *shell, bool pipe)
{
	if (commands->redirections)
		get_fds(commands->redirections, shell);
	close_fds(shell);
	if (commands->cmd_name[1])
	{
		if (get_exit_status(commands, commands->cmd_name[1], shell, pipe) == 1)
			return ;
	}
	else if (pipe == false)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	free_and_exit_shell(shell, shell->exit_status);
}
