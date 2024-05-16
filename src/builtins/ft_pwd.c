/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:10:39 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/16 13:21:36 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_command *commands)
{
	char	cwd[4096]; // = PATH_MAX on the system (getconf -a PATH_MAX)

	if (commands->cmd_name[1] && commands->cmd_name[1][0] && commands->cmd_name[1][0] == '-')
	{
		write_error(commands->cmd_name[1], "invalid option");
		return (2);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd");
		return (1);
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

// int	ft_export()
// {

// }

// int	ft_unset()
// {

// }

// int	ft_env()
// {

// }
