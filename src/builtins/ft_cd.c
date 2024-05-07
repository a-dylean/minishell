/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:44:36 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/07 10:04:29 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_minus(t_shell *shell, int option)
{
	char *temp;

	temp = ft_strdup(shell->prev_dir);
	if (shell->prev_dir == NULL)
	{
		ft_putstr_fd(shell->cur_dir, STDERR_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	if (chdir(shell->prev_dir) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(shell->prev_dir);
		return (1);
	}
	else
	{
		shell->prev_dir = ft_strdup(shell->cur_dir);
		shell->cur_dir = ft_strdup(temp);
		if (option == 1)
		{
			ft_putstr_fd(shell->cur_dir, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
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

void	update_working_directory(t_shell *shell)
{
	char	cwd[4096]; // = PATH_MAX on the system (getconf -a PATH_MAX)

	if (shell->prev_dir)
		free(shell->prev_dir);
	shell->prev_dir = ft_strdup(shell->cur_dir);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("pwd");
	if (shell->cur_dir)
		free(shell->cur_dir);
	shell->cur_dir = ft_strdup(cwd);
}

void	init_directories(t_shell *shell)
{
	char	cwd[4096]; // = PATH_MAX on the system (getconf -a PATH_MAX)

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("pwd");
	shell->cur_dir = ft_strdup(cwd);
}

int	ft_cd(t_command *commands, t_shell *shell)
{
	if (shell->cur_dir == NULL)
		init_directories(shell);
	if (commands->cmd_name[2])
	{
		write_error("cd", "too many arguments");
		return (1);
	}
	if (!commands->cmd_name[1])
	{
		if (chdir(getenv("HOME")) == -1)
		{
			ft_putstr_fd("minishell: cd :", STDERR_FILENO);
			perror("");
			return (1);
		}
		update_working_directory(shell);
		return (0);
	}
	return (check_for_arguments(commands, shell));
}

