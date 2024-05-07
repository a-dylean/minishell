/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:48:58 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/07 16:38:15 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_if_directory(char *cmd, t_shell *shell)
{
	struct stat path_stat;

	// if (stat(cmd, &path_stat) == -1)
	// {
	// 	perror(cmd);
	// 	shell->exit_status = 1;
	// 	free_and_exit_shell(shell, shell->exit_status);
	// }
	stat(cmd, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		write_error(cmd, "Is a directory");
		shell->exit_status = 126;
		free_and_exit_shell(shell, shell->exit_status);
	}
	else if (access(cmd, X_OK) == 0)
		return (cmd);
	if (!S_ISDIR(path_stat.st_mode))
	{
		if (access(cmd, F_OK) == -1)
		{
			write_error(cmd, "No such file or directory");
			shell->exit_status = 127;
			free_and_exit_shell(shell, shell->exit_status);
		}
		else
			shell->exit_status = 126;
		return (cmd);
	}
	else
		return (NULL);
}

char	*search_executable_cmd(char **path_dirs, char *cmd)
{
	char	*cmd_path;
	char	*temp;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		temp = ft_strjoin(path_dirs[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free(temp);
			free_array(path_dirs);
			return (cmd_path);
		}
		free(cmd_path);
		free(temp);
		i++;
	}
	free_array(path_dirs);
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_shell *shell)
{
	char	**path_dirs;
	char	*path_var;

	if (ft_strchr(cmd, '/') != NULL)
		return (check_if_directory(cmd, shell));
	path_var = getenv("PATH");
	if (!path_var)
		return (NULL);
	path_dirs = ft_split(path_var, ':');
	if (!path_dirs)
		return (NULL);
	return (search_executable_cmd(path_dirs, cmd));
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
