/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:44:36 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/15 17:46:17 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_minus(t_shell *shell, int option)
{
	char *curr_dir;
	char *old_dir;

	curr_dir = ft_getenv(shell->env_head, "OLDPWD");
	old_dir = ft_getenv(shell->env_head, "PWD");
	if (!curr_dir)
	{
		write_error("cd", "OLDPWD not set");
		if (old_dir)
			free(old_dir);
		return (1);
	}
	else if (!old_dir)
	{
		write_error("cd", "PWD not set");
		if (curr_dir)
			free(curr_dir);
		return (1);
	}
	if (curr_dir && chdir(curr_dir) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(shell->prev_dir);
		free(curr_dir);
		if (old_dir)
			free(old_dir);
		return (1);
	}
	if (option == 1)
	{
		ft_putstr_fd(curr_dir, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	ft_setenv(shell->env_head, "PWD", curr_dir);
	ft_setenv(shell->env_head, "OLDPWD", old_dir);
	if (curr_dir)
		free(curr_dir);
	if (old_dir)
		free(old_dir);
	return (0);
}

int	check_for_arguments(t_command *commands, t_shell *shell)
{
	if (commands->cmd_name[1])
	{
		if (commands->cmd_name[1][0] == '-' && !commands->cmd_name[1][1])
			return (cd_minus(shell, 1));
		else if (commands->cmd_name[1][0] == '-' && commands->cmd_name[1][1] == '-' && !commands->cmd_name[1][2])
			return (cd_minus(shell, 0));
		else if (chdir(commands->cmd_name[1]) == -1)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			perror(commands->cmd_name[1]);
			return (1);
		}
	}
	return (0);
}

int	ft_cd(t_command *commands, t_shell *shell)
{
	char	*value;

	if (commands->cmd_name[0] && commands->cmd_name[1] && commands->cmd_name[2])
	{
		write_error("cd", "too many arguments");
		return (1);
	}
	if (!commands->cmd_name[1])
	{
		value = ft_getenv(shell->env_head, "HOME");
		if (!value)
		{
			write_error("cd", "HOME not set");
			return (1);
		}
		if (chdir(value) == -1)
		{
			ft_putstr_fd("minishell: cd :", STDERR_FILENO);
			perror("");
			return (1);
		}
		return (0);
	}
	return (check_for_arguments(commands, shell));
}

