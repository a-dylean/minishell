/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:44:36 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/30 13:34:38 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_command *commands, t_shell *shell)
{
	(void)shell;
	if (commands->cmd_name[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (!commands->cmd_name[1]) // if cd is called without arguments, it should go to the home directory
	{
		if (chdir(getenv("HOME")) == -1)
		{
			ft_putstr_fd("minishell: cd :", STDERR_FILENO);
			perror("");
			return (1);
		}
		return (0);
	}
	if (chdir(commands->cmd_name[1]) == -1) // if cd is called with an argument, it should go to that directory
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(commands->cmd_name[1]);
		return (1);
	}
	return (0);
}

// int	ft_cd_home(t_shell *shell)
// {
// 	if (chdir(getenv("HOME")) == -1)
// 	{
// 		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
// 		perror(shell->home);
// 		return (1);
// 	}
// 	return (0);
// }

// int	ft_cd(t_command *commands, t_shell *shell)
// {
// 	if (!commands->next)
// 		return (ft_cd_home(shell));
// 	if (commands->cmd_name[2])
// 	{
// 		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
// 		return (1);
// 	}
// 	// if (ft_strcmp(commands->cmd_name[1], "-") == 0)
// 	// 	return (ft_cd_oldpwd(shell));
// 	// else if ()
// }