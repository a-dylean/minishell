/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:18:11 by jlabonde          #+#    #+#             */
/*   Updated: 2024/03/11 14:51:08 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_fds(t_struct *pipex, int is_last)
{
	if (pipex->is_first)
		open_infile(pipex);
	if (!is_last)
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	else
	{
		pipex->outfile_fd = open(pipex->outfile_name, O_WRONLY | O_TRUNC
				| O_CREAT, 0666);
		if (pipex->outfile_fd == -1)
			exit_error(pipex->outfile_name, pipex, 1, 0);
		dup2(pipex->outfile_fd, STDOUT_FILENO);
		close(pipex->outfile_fd);
	}
	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
}

char	*check_path(char *cmd, t_struct *pipex)
{
	char	*tmp;
	char	*path;
	char	**possible_paths;
	int		i;

	i = 0;
	possible_paths = ft_split(find_path(pipex), ':');
	if (possible_paths == NULL)
		exit_error("malloc", pipex, 1, 0);
	while (possible_paths[i])
	{
		tmp = ft_strjoin(possible_paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (possible_paths[++i])
		free(possible_paths[i]);
	if (possible_paths)
		free(possible_paths);
	return (NULL);
}

void	pipex_init(int ac, char **av, char **ev, t_struct *pipex)
{
	pipex->exit_code_child = 1;
	pipex->is_bonus = (ft_strnstr(av[0], "_bonus", ft_strlen(av[0]))) != NULL;
	if ((pipex->is_bonus == 0 && ac != 5) || (pipex->is_bonus == 1 && ac < 5))
		exit_error(USAGE, pipex, 0, 0);
	pipex->outfile_name = av[ac - 1];
	pipex->infile_name = av[1];
	pipex->env = ev;
	pipex->is_first = 1;

}

void	exec(char *cmd, t_struct *pipex, int is_last)
{
	int	i;

	i = -1;
	open_fds(pipex, is_last);
	pipex->command = ft_split(cmd, ' ');
	if (pipex->command[0] == NULL)
		exit_error("Command not found", pipex, 1, 127);
	get_path(pipex);
	if (!pipex->path)
	{
		while (pipex->command[++i])
			free(pipex->command[i]);
		exit_error("Command not found", pipex, 1, 127);
	}
	else
	{
		execve(pipex->path, pipex->command, pipex->env);
		perror(pipex->path);
		pipex->exit_code_child = 126;
	}
	free(pipex->path);
	ft_free(pipex->command);
	exit(pipex->exit_code_child);
}

int	main(int ac, char **av, char **ev)
{
	t_struct	pipex;

	pipex_init(ac, av, ev, &pipex);
	av++;
	while (*(++av + 1))
	{
		if (pipe(pipex.pipe_fd) == -1)
			exit_error("pipe", &pipex, 0, 0);
		pipex.last_pid = fork();
		if (pipex.last_pid == -1)
			exit_error("fork", &pipex, 1, 0);
		if (pipex.last_pid == 0)
			exec(*av, &pipex, *(av + 2) == NULL);
		dup2(pipex.pipe_fd[0], STDIN_FILENO);
		close(pipex.pipe_fd[0]);
		close(pipex.pipe_fd[1]);
		pipex.is_first = 0;
	}
	return (wait_commands(&pipex));
}
