/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:45:38 by jlabonde          #+#    #+#             */
/*   Updated: 2024/03/08 15:31:31 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(char *str, t_struct *pipex, int close_fds, int exit_code)
{
	perror(str);
	if (close_fds)
	{
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
	}
	if (exit_code == 127)
	{
		free(pipex->command);
		pipex->exit_code_child = 127;
	}
	exit(pipex->exit_code_child);
}

void	get_path(t_struct *pipex)
{
	if (ft_strchr(*pipex->command, '/') != NULL
		&& access(*pipex->command, X_OK) == 0)
		pipex->path = ft_strdup(*pipex->command);
	else
		pipex->path = check_path(*pipex->command, pipex);
}

char	*find_path(t_struct *pipex)
{
	while (*pipex->env)
	{
		if (ft_strncmp("PATH", *pipex->env, 4) == 0)
			return (*pipex->env + 5);
		pipex->env++;
	}
	return (NULL);
}

void	open_infile(t_struct *pipex)
{
	pipex->infile_fd = open(pipex->infile_name, O_RDONLY);
	if (pipex->infile_fd == -1)
		exit_error(pipex->infile_name, pipex, 1, 0);
	dup2(pipex->infile_fd, STDIN_FILENO);
	close(pipex->infile_fd);
}

int	wait_commands(t_struct *pipex)
{
	int	ret;

	ret = 0;
	while (errno != ECHILD)
	{
		if (wait(&pipex->wstatus) == pipex->last_pid)
		{
			if (WIFEXITED(pipex->wstatus))
				ret = WEXITSTATUS(pipex->wstatus);
			else
				ret = 128 + WTERMSIG(pipex->wstatus);
		}
	}
	return (ret);
}
