/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:44:36 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/23 13:20:18 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_command *commands)
{
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
	else if (chdir(commands->cmd_name[1]) == -1) // if cd is called with an argument, it should go to that directory
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(commands->cmd_name[1]);
		return (1);
	}
	return (0);
}
