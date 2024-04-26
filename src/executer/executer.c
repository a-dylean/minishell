/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:34:18 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/26 14:57:32 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_builtin(t_command *commands)
{
	int		status;

	status = 0;
	if (ft_strcmp(commands->cmd_name[0], "cd") == 0)
		status = ft_cd(commands);
	else if (ft_strcmp(commands->cmd_name[0], "pwd") == 0)
	 	status = ft_pwd();
	else if (ft_strcmp(commands->cmd_name[0], "echo") == 0)
		status = ft_echo(commands->cmd_name);
	// else if (ft_strcmp(commands->cmd_name[0], "export") == 0)
	// 	status = ft_export();
	// else if (ft_strcmp(commands->cmd_name[0], "unset") == 0)
	// 	status = ft_unset();
	// else if (ft_strcmp(commands->cmd_name[0], "env") == 0)
	// 	status = ft_env();
	else if (ft_strcmp(commands->cmd_name[0], "exit") == 0)
		status = ft_exit(commands);
	exit(status);
}
char	*get_cmd_path(char *cmd)
{
	char	**path_dirs;
	char	*path_var;
	char	*cmd_path;
	int		i;

	i = 0;
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

void	get_fd_in(t_token *redirections, t_shell *shell)
{
	t_token	*current;

	current = redirections;
	while (current)
	{
		if (current->type == LESS || current->type == LESSLESS)
		{
			if (current->next && current->next->type == FILENAME)
			{
				if (shell->infile_fd != -2)
					close(shell->infile_fd);
				shell->infile_fd = open(current->next->value, O_RDONLY);
			}
		}
		if (shell->infile_fd == -1)
		{
			perror(current->next->value);
			exit(EXIT_FAILURE);
		}
		current = current->next;
	}
}

void	open_outfile(char *filename, t_shell *shell, int flags)
{
	if (shell->outfile_fd != -2)
		close(shell->outfile_fd);
	if (flags == GREAT)
		shell->outfile_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		shell->outfile_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	get_fd_out(t_token *redirections, t_shell *shell)
{
	t_token	*current;

	current = redirections;
	while (current)
	{
		if (current->next && current->next->type == FILENAME)
		{
			if (current->type == GREAT)
				open_outfile(current->next->value, shell, GREAT);
			else if (current->type == GREATGREAT)
				open_outfile(current->next->value, shell, GREATGREAT);
		}
		if (shell->outfile_fd == -1)
		{
			perror(current->next->value);
			exit(EXIT_FAILURE);
		}
		current = current->next;
	}
}

void	executer(t_command *commands, t_shell *shell)
{
	t_command	*current;
	int			prev_fd;
	pid_t		pids[100];
	int			n = 0;
	current = commands;
	prev_fd = 0;
	while (current)
	{
		if (current->next)
		{
			if (pipe(shell->pipe_fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pid_t	pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) // child process
		{
			if (current->redirections)
			{
				get_fd_in(current->redirections, shell);
				get_fd_out(current->redirections, shell);
				if (shell->infile_fd != -2)
				{
					if (dup2(shell->infile_fd, STDIN_FILENO) == -1)
					{
						perror("dup2");
						exit(EXIT_FAILURE);
					}
				}
				if (shell->outfile_fd != -2)
				{
					if (dup2(shell->outfile_fd, STDOUT_FILENO) == -1)
					{
						perror("dup2");
						exit(EXIT_FAILURE);
					}
				}
			}
			if (prev_fd != 0)
			{
				if (dup2(prev_fd, STDIN_FILENO) == -1)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			if (current->next && !current->redirections)
			{
				if (dup2(shell->pipe_fd[1], STDOUT_FILENO) == -1)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
				close(shell->pipe_fd[0]);
			}
			// execute the command
			if (current->is_builtin == true)
				exec_builtin(current);
			else
			{
				shell->cmd_path = get_cmd_path(current->cmd_name[0]);
				if (!shell->cmd_path)
				{
					fprintf(stderr, "%s: command not found\n", current->cmd_name[0]);
					exit(EXIT_FAILURE);
				}
				execve(shell->cmd_path, current->cmd_name, shell->env);
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			// parent process
			pids[n++] = pid; // find another way to store the pids
			if (prev_fd != 0)
				close(prev_fd);
			if (current->next)
			{
				close(shell->pipe_fd[1]);
				prev_fd = shell->pipe_fd[0];
			}
			if (shell->infile_fd != -1)
				close(shell->infile_fd);
			if (shell->outfile_fd != -1)
				close(shell->outfile_fd);
		}
		current = current->next;
	}
	for (int i = 0; i < n; i++)
		waitpid(pids[i], NULL, 0);
}