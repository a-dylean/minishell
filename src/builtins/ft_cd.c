/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:44:36 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/30 14:57:54 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_pwd(t_shell *shell, char *command)
{
	char	cwd[4096];
	char	*old_dir;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(command);
		return ;
	}
	old_dir = ft_getenv(shell->env_list, "PWD");
	if (!old_dir)
		return ;
	ft_setenv(shell->env_list, "OLDPWD", old_dir);
	free(old_dir);
	ft_setenv(shell->env_list, "PWD", cwd);
}

int	cd_minus(t_shell *shell, int option)
{
	char	*curr_dir;
	char	*old_dir;

	curr_dir = ft_getenv(shell->env_list, "OLDPWD");
	old_dir = ft_getenv(shell->env_list, "PWD");
	if (!curr_dir)
	{
		write_error("cd", "OLDPWD not set", NULL);
		return (free_and_return(curr_dir, old_dir, 1));
	}
	else if (!old_dir)
	{
		write_error("cd", "PWD not set", NULL);
		return (free_and_return(curr_dir, old_dir, 1));
	}
	if (curr_dir && chdir(curr_dir) == -1)
		return (handle_chdir_error(curr_dir, old_dir));
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
		else if (commands->cmd_name[1][0] == '-' && commands->cmd_name[1][1])
		{
			write_error("cd", "invalid option", commands->cmd_name[1]);
			return (2);
		}
		else if (chdir(commands->cmd_name[1]) == -1)
		{
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			perror(commands->cmd_name[1]);
			return (1);
		}
		update_pwd(shell, commands->cmd_name[1]);
	}
	return (0);
}

int	ft_cd(t_command *commands, t_shell *shell)
{
	char	*value;

	if (commands->cmd_name[0] && commands->cmd_name[1] && commands->cmd_name[2])
	{
		write_error("cd", "too many arguments", NULL);
		return (1);
	}
	if (!commands->cmd_name[1])
	{
		value = ft_getenv(shell->env_list, "HOME");
		if (!value)
			return (write_error("cd", "HOME not set", NULL), free(value), 1);
		if (ft_strlen(value) == 0)
		{
			free(value);
			value = getcwd(NULL, 0);
		}
		if (chdir(value) == -1)
			return (perror("minishell: cd:"), free(value), 1);
		update_pwd(shell, commands->cmd_name[0]);
		free(value);
	}
	return (check_for_arguments(commands, shell));
}
