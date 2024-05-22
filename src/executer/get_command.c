/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:04:00 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/22 16:14:51 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_error(char *cmd, char *error,
				int exit_status, t_shell *shell)
{
	write_error(cmd, error, NULL);
	shell->exit_status = exit_status;
	free_and_exit_shell(shell, shell->exit_status);
}

static char	*check_if_directory(char *cmd, t_shell *shell)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == -1)
	{
		perror(cmd);
		shell->exit_status = 127;
		free_and_exit_shell(shell, shell->exit_status);
	}
	stat(cmd, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		handle_error(cmd, "Is a directory", 126, shell);
	else if (access(cmd, X_OK) == 0)
		return (cmd);
	if (!S_ISDIR(path_stat.st_mode))
	{
		if (access(cmd, F_OK) == -1)
			handle_error(cmd, "No such file or directory", 127, shell);
		else
			shell->exit_status = 126;
		return (cmd);
	}
	return (NULL);
}

static char	*search_executable_cmd(char **path_dirs, char *cmd)
{
	char	*cmd_path;
	char	*temp;
	int		i;

	i = 0;
	if (cmd[0] == '\0')
	{
		free_array(path_dirs);
		return (NULL);
	}
	while (path_dirs[i++])
	{
		temp = ft_strjoin(path_dirs[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		if (cmd_path && access(cmd_path, X_OK) == 0)
		{
			free(temp);
			free_array(path_dirs);
			return (cmd_path);
		}
		free(cmd_path);
		free(temp);
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
	path_var = ft_getenv(shell->env_list, "PATH");
	if (!path_var)
		return (NULL);
	path_dirs = ft_split(path_var, ':');
	if (!path_dirs)
		return (free(path_var), NULL);
	free(path_var);
	return (search_executable_cmd(path_dirs, cmd));
}
