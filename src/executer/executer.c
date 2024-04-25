/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:34:18 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/25 11:37:40 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_builtin(t_command *commands)
{
	if (ft_strcmp(commands->cmd_name[0], "cd") == 0)
		ft_cd(commands);
	else if (ft_strcmp(commands->cmd_name[0], "pwd") == 0)
	 	ft_pwd();
	// else if (ft_strcmp(commands->cmd_name[0], "echo") == 0)
	// 	ft_echo(commands);
	// else if (ft_strcmp(commands->cmd_name[0], "export") == 0)
	// 	ft_export();
	// else if (ft_strcmp(commands->cmd_name[0], "unset") == 0)
	// 	ft_unset();
	// else if (ft_strcmp(commands->cmd_name[0], "env") == 0)
	// 	ft_env();
	else if (ft_strcmp(commands->cmd_name[0], "exit") == 0)
		ft_exit(commands);
}

// simple loop for testing purposes, does not handle pipes
// void	executer(t_command *commands)
// {
// 	t_command	*current;

// 	current = commands;
// 	while (current)
// 	{
// 		if (current->is_builtin)
// 			exec_builtin(current); // handles the builtins 
// 		// else
// 		// 	exec_cmd(current); // will execute the other commands
// 		current = current->next;
// 	}
// }

char	*get_cmd_path(char *cmd)
{
    char	**path_dirs;
    char	*path_var;
    char	*cmd_path;
    int		i;

    path_var = getenv("PATH");
    if (!path_var)
        return (NULL);
    path_dirs = ft_split(path_var, ':');
    if (!path_dirs)
        return (NULL);
    i = 0;
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

int	get_fd_in(t_token *redirections)
{
	t_token	*current;
	int	in_fd;

	in_fd = -2;
	current = redirections;
	while (current)
	{
		if (current->type == LESS || current->type == LESSLESS)
		{
			if (current->next && current->next->type == FILENAME)
			{
				if (in_fd != -2)
					close(in_fd);
				in_fd = open(current->next->value, O_RDONLY);
			}
		}
		if (in_fd == -1)
		{
			perror(current->next->value);
			exit(EXIT_FAILURE);
		}
		current = current->next;
	}
	return (in_fd);
}

int	get_fd_out(t_token *redirections)
{
	t_token	*current;
	int		out_fd;

	out_fd = -2;
	current = redirections;
	while (current)
	{
		if (current->type == GREAT)
		{
			if (current->next && current->next->type == FILENAME)
			{
				if (out_fd != -2)
					close(out_fd);
				out_fd = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
		}
		else if (current->type == GREATGREAT)
		{
			if (current->next && current->next->type == FILENAME)
			{
				if (out_fd != -2)
					close(out_fd);
				out_fd = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			}
		}
		if (out_fd == -1)
		{
			perror(current->next->value);
			exit(EXIT_FAILURE);
		}
		current = current->next;
	}
	return (out_fd);
}

// void	get_path(char *cmd, t_struct *pipex)
// {
// 	if (ft_strchr(cmd, '/') != NULL
// 		&& access(cmd, X_OK) == 0)
// 		pipex->path = ft_strdup(cmd);
// 	else
// 		pipex->path = get_cmd_path(cmd);
// }

// int	wait_commands(t_struct *pipex)
// {
// 	int	ret;

// 	ret = 0;
// 	while (errno != ECHILD)
// 	{
// 		if (wait(&pipex->wstatus) == pipex->last_pid)
// 		{
// 			if (WIFEXITED(pipex->wstatus))
// 				ret = WEXITSTATUS(pipex->wstatus);
// 			else
// 				ret = 128 + WTERMSIG(pipex->wstatus);
// 		}
// 	}
// 	return (ret);
// }

// void	exec(t_command *command, t_struct *pipex, int is_last)
// {
// 	int	original_stdout = dup(STDOUT_FILENO);
// 	if (pipex->is_first)
// 		pipex->infile_fd = get_fd_in(command->redirections);
// 	if (!is_last)
// 	{
// 		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
// 		close(pipex->pipe_fd[0]);
// 		close(pipex->pipe_fd[1]);
// 	}
// 	else
// 	{
// 		pipex->outfile_fd = get_fd_out(command->redirections);
// 		dup2(pipex->outfile_fd, STDOUT_FILENO);
// 		close(pipex->outfile_fd);
// 		close(pipex->pipe_fd[0]);
// 		close(pipex->pipe_fd[1]);
// 	}
// 	// this above can be put in a separate function like in pipex open_fds
// 	get_path(command->cmd_name[0], pipex);
// 	if (!pipex->path)
// 		exit(127); // command not found
// 	else
// 	{
// 		execve(pipex->path, command->cmd_name, pipex->env);
// 		perror(pipex->path);
// 		//exit(126);
// 	}
// 	dup2(original_stdout, STDOUT_FILENO);
//     close(original_stdout);
// }

// void	pipex_init(t_struct *pipex, t_shell *shell)
// {
// 	pipex->exit_code_child = 1;
// 	pipex->is_first = 1;
// 	pipex->path = NULL;
// 	pipex->infile_fd = -2;
// 	pipex->outfile_fd = -2;
// 	pipex->env = shell->env;
// }

// void	executer(t_command *commands, t_shell *shell)
// {
// 	t_command	*current;
// 	t_struct	pipex;

// 	printf("Starting executer function\n");
// 	pipex_init(&pipex, shell);
// 	(void) shell;
// 	current = commands;
// 	while(current)
// 	{
// 		printf("Executing command: %s\n", current->cmd_name[0]);
// 		if (pipe(pipex.pipe_fd) == -1)
// 			return ; //exit_error("pipe", &pipex, 0, 1);
// 		pipex.last_pid = fork();
// 		if (pipex.last_pid == -1)
// 			perror("fork"); // exit_error("fork", &pipex, 1, 1);
// 		if (pipex.last_pid == 0)
// 			exec(current, &pipex, current->next == NULL);
// 		else
// 		{
// 			if (current->next != NULL)
// 				dup2(pipex.pipe_fd[0], STDIN_FILENO);
// 			else
// 			{
// 				// This is the last command in the pipeline, restore the standard input
// 				dup2(pipex.pipe_fd[1], STDIN_FILENO);
// 			}
// 			close(pipex.pipe_fd[0]);
// 			close(pipex.pipe_fd[1]);
// 			waitpid(pipex.last_pid, NULL, 0);
// 			pipex.is_first = 0;
// 			current = current->next;
// 		}
// 	}
// 	printf("Finished executing commands\n");
// 	pipex.exit_code_child = wait_commands(&pipex);
// }

void	executer(t_command *commands, t_shell *shell)
{
	t_command	*current;
	int			pipe_fd[2];
	int			prev_fd;
	char		*cmd_path;
	int	fd_in, fd_out;
	pid_t		pids[100];
	int			n = 0;
	current = commands;
	prev_fd = 0;
	while (current)
	{
		fd_in = -1;
		fd_out = -1;
		if (current->next)
		{
			if (pipe(pipe_fd) == -1)
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
				fd_in = get_fd_in(current->redirections);
				fd_out = get_fd_out(current->redirections);
				if (fd_in != -2)
				{
					if (dup2(fd_in, STDIN_FILENO) == -1)
					{
						perror("dup2");
						exit(EXIT_FAILURE);
					}
				}
				if (fd_out != -2)
				{
					if (dup2(fd_out, STDOUT_FILENO) == -1)
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
			if (current->next)
			{
				if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			// execute the command
			if (current->is_builtin == true)
				exec_builtin(current);
			else
			{
				cmd_path = get_cmd_path(current->cmd_name[0]);
				if (!cmd_path)
				{
					fprintf(stderr, "%s: command not found\n", current->cmd_name[0]);
					exit(EXIT_FAILURE);
				}
				execve(cmd_path, current->cmd_name, shell->env);
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
				close(pipe_fd[1]);
				prev_fd = pipe_fd[0];
			}
			if (fd_in != -1)
				close(fd_in);
			if (fd_out != -1)
				close(fd_out);			
		}
		current = current->next;
	}
	for (int i = 0; i < n; i++)
		waitpid(pids[i], NULL, 0);
}