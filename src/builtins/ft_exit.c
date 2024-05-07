/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:43:34 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/07 10:15:43 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	compute_exit_status(long stat, t_shell *shell)
{
	if (stat > 255)
		stat = stat % 256;
	else if (stat < 0)
		stat = (stat % 256) + 256;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	shell->exit_status = stat;
}

static int	get_exit_status(t_command *commands, char *arg, t_shell *shell)
{
	long stat;

	stat = ft_atol(arg);
	if (errno == ERANGE)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		// ft_putstr_fd("") add the problamatic argument here
		write_error("exit", "numeric argument required");
		shell->exit_status = 2;
	}
	else if (commands->cmd_name[1] && commands->cmd_name[2])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		write_error("exit", "too many arguments");
		shell->exit_status = 1;
		return (1);
	}
	else
		compute_exit_status(stat, shell);
	return (0);
}
// we need to add functions handling the freeing of the commands structure
void	ft_exit(t_command *commands, t_shell *shell)
{
	int	exit_status;

	if (commands->cmd_name[1])
	{
		if (get_exit_status(commands, commands->cmd_name[1], shell) == 1)
			return ;
	}
	else // means there is no number after exit
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit_status = shell->exit_status;
	free_shell(shell);
	exit(exit_status); // here, it should exit with the last commands exit status
}
