/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:34:18 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/02 15:24:17 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_builtin(t_command *commands, t_shell *shell)
{
	if (ft_strcmp(commands->cmd_name[0], "cd") == 0)
		shell->exit_status = ft_cd(commands, shell);
	else if (ft_strcmp(commands->cmd_name[0], "pwd") == 0)
		shell->exit_status = ft_pwd();
	else if (ft_strcmp(commands->cmd_name[0], "echo") == 0)
		shell->exit_status = ft_echo(commands);
	// else if (ft_strcmp(commands->cmd_name[0], "export") == 0)
	// 	shell->exit_status = ft_export();
	// else if (ft_strcmp(commands->cmd_name[0], "unset") == 0)
	// 	shell->exit_status = ft_unset();
	// else if (ft_strcmp(commands->cmd_name[0], "env") == 0)
	// 	shell->exit_status = ft_env();
	else if (ft_strcmp(commands->cmd_name[0], "exit") == 0)
		ft_exit(commands, shell);
	exit(shell->exit_status);
}
void	exec_single_builtin(t_command *commands, t_shell *shell)
{
	if (ft_strcmp(commands->cmd_name[0], "cd") == 0)
		shell->exit_status = ft_cd(commands, shell);
	else if (ft_strcmp(commands->cmd_name[0], "pwd") == 0)
		shell->exit_status = ft_pwd();
	else if (ft_strcmp(commands->cmd_name[0], "echo") == 0)
		shell->exit_status = ft_echo(commands);
	// else if (ft_strcmp(commands->cmd_name[0], "export") == 0)
	// 	shell->exit_status = ft_export();
	// else if (ft_strcmp(commands->cmd_name[0], "unset") == 0)
	// 	shell->exit_status = ft_unset();
	// else if (ft_strcmp(commands->cmd_name[0], "env") == 0)
	// 	shell->exit_status = ft_env();
	else if (ft_strcmp(commands->cmd_name[0], "exit") == 0)
		ft_exit(commands, shell);
}

void	pipe_and_fork(t_command *current, t_shell *shell)
{
	if (current->next)
	{
		if (pipe(shell->pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	shell->last_pid = fork();
	if (shell->last_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	execute_command(t_command *current, t_shell *shell)
{
	signal(SIGQUIT, SIG_DFL);
	if (current->is_builtin == true)
		exec_builtin(current, shell);
	else
	{
		shell->cmd_path = get_cmd_path(current->cmd_name[0], shell);
		if (shell->exit_status == 126)
			return ;
		if (!shell->cmd_path)
		{
			fprintf(stderr, "%s: command not found\n", current->cmd_name[0]); // change to ft_putstr_fd
			shell->exit_status = 127;
			exit(shell->exit_status);
		}
		execve(shell->cmd_path, current->cmd_name, shell->env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int	handle_parent(t_command *current, t_shell *shell, int prev_fd)
{
	if (prev_fd != 0)
		close(prev_fd);
	if (current->next)
	{
		close(shell->pipe_fd[1]);
		prev_fd = shell->pipe_fd[0];
	}
	if (shell->infile_fd >= 0)
		close(shell->infile_fd);
	if (shell->outfile_fd >= 0)
		close(shell->outfile_fd);
	return (prev_fd);
}

int	executer(t_shell *shell)
{
	t_command	*current;
	int			prev_fd;

	if (shell == NULL || shell->commands == NULL)
        return -1;
	current = shell->commands;
	prev_fd = 0;
	if (!current->next && current->is_builtin == true && !current->redirections)
		exec_single_builtin(current, shell);
	else
	{
		while (current)
		{
			pipe_and_fork(current, shell);
			if (shell->last_pid == 0) // child process
			{
				if (current->redirections)
					open_and_redirect_fd(current, shell);
				has_no_filename(current, shell, prev_fd);
				execute_command(current, shell);
			}
			else
				prev_fd = handle_parent(current, shell, prev_fd);
			current = current->next;
		}
	}
	wait_commands(shell);
	return (shell->exit_status);
}
