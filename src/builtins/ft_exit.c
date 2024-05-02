/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:43:34 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/02 12:49:41 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_exit_code(char *arg, t_shell *shell)
{
	long stat;

	stat = ft_atol(arg);
	if (errno == ERANGE)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		shell->exit_status = 2;
	}
	else
	{
		if (stat > 255)
			stat = stat % 256;
		else if (stat < 0)
			stat = (stat % 256) + 256;
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		shell->exit_status = stat;
	}
}
// we need to add functions handling the freeing of the commands structure
int	ft_exit(t_command *commands, t_shell *shell)
{
	if (commands->cmd_name[1] && commands->cmd_name[2])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		shell->exit_status = 1;
	}
	else if (commands->cmd_name[1] == NULL) // means there is no number after exit
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(shell->exit_status); // here, it should exit with the last commands exit status, we need to modify it
	}
	else if (commands->cmd_name[1] != NULL) // there is a number after exit, we need to exit with that number
	{
		get_exit_code(commands->cmd_name[1], shell);
		exit(shell->exit_status);
	}
	return (0);
}
