/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:48:58 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/02 16:00:03 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cmd_path(char *cmd, t_shell *shell)
{
	char	**path_dirs;
	char	*path_var;
	char	*cmd_path;
	int		i;
	struct stat path_stat;

	i = 0;
	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "/", 1) == 0)
	{
		stat(cmd, &path_stat);
		if (!S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			shell->exit_status = 127;
			return (cmd);
		}
	}
	if (ft_strchr(cmd, '/') != NULL)
	{
		stat(cmd, &path_stat);
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd, STDERR_FILENO);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			shell->exit_status = 126;
			return (cmd);
		}
		else if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			return (NULL);
	}
	path_var = getenv("PATH");
	if (!path_var)
		return (NULL);
	path_dirs = ft_split(path_var, ':');
	if (!path_dirs)
		return (NULL);
	while (path_dirs[i])
	{
		cmd_path = ft_strjoin(path_dirs[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		i++;
	}
	return (NULL);
}

void	wait_commands(t_shell *shell)
{
	signal(SIGINT, SIG_IGN);
	while (errno != ECHILD)
	{
		if (wait(&shell->wstatus) == shell->last_pid)
		{
			if (WIFEXITED(shell->wstatus))
				shell->exit_status = WEXITSTATUS(shell->wstatus);
			else
				shell->exit_status = 128 + WTERMSIG(shell->wstatus);
		}
	}
	signal(SIGINT, catch_sigint);
}
