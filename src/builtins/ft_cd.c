/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:44:36 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/17 16:22:06 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_and_return(char *curr_dir, char *old_dir, int ret)
{
	if (curr_dir)
		free(curr_dir);
	if (old_dir)
		free(old_dir);
	return (ret);
}

int	handle_chdir_error(t_shell *shell, char *curr_dir, char *old_dir)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	perror(shell->prev_dir);
	return (free_and_return(curr_dir, old_dir, 1));
}

int	cd_minus(t_shell *shell, int option)
{
	char	*curr_dir;
	char	*old_dir;

	curr_dir = ft_getenv(shell->env_list, "OLDPWD");
	old_dir = ft_getenv(shell->env_list, "PWD");
	if (!curr_dir)
	{
		write_error("cd", "OLDPWD not set");
		return (free_and_return(curr_dir, old_dir, 1));
	}
	else if (!old_dir)
	{
		write_error("cd", "PWD not set");
		return (free_and_return(curr_dir, old_dir, 1));
	}
	if (curr_dir && chdir(curr_dir) == -1)
		return (handle_chdir_error(shell, curr_dir, old_dir));
	if (option == 1)
	{
		ft_putstr_fd(curr_dir, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	ft_setenv(shell->env_list, "PWD", curr_dir);
	ft_setenv(shell->env_list, "OLDPWD", old_dir);
	return (free_and_return(curr_dir, old_dir, 0));
}

int	check_for_arguments(t_command *commands, t_shell *shell)
{
	if (commands->cmd_name[1])
	{
		if (commands->cmd_name[1][0] == '-' && !commands->cmd_name[1][1])
			return (cd_minus(shell, 1));
		else if (commands->cmd_name[1][0] == '-'
				&& commands->cmd_name[1][1] == '-' && !commands->cmd_name[1][2])
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
		value = ft_getenv(shell->env_list, "HOME");
		if (!value)
		{
			write_error("cd", "HOME not set");
			return (1);
		}
		if (chdir(value) == -1)
		{
			ft_putstr_fd("minishell: cd :", STDERR_FILENO);
			perror("");
			free(value);
			return (1);
		}
		free(value);
	}
	return (check_for_arguments(commands, shell));
}
