/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:34:18 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/16 19:57:58 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_builtin(t_command *commands, t_shell *shell)
{
	if (ft_strcmp(commands->cmd_name[0], "cd") == 0)
		shell->exit_status = ft_cd(commands, shell);
	else if (ft_strcmp(commands->cmd_name[0], "pwd") == 0)
		shell->exit_status = ft_pwd(commands);
	else if (ft_strcmp(commands->cmd_name[0], "echo") == 0)
		shell->exit_status = ft_echo(commands);
	else if (ft_strcmp(commands->cmd_name[0], "export") == 0)
		shell->exit_status = ft_export(commands->cmd_name, shell);
	else if (ft_strcmp(commands->cmd_name[0], "unset") == 0)
		shell->exit_status = ft_unset(commands->cmd_name, shell);
	else if (ft_strcmp(commands->cmd_name[0], "env") == 0)
		shell->exit_status = ft_env(shell);
	else if (ft_strcmp(commands->cmd_name[0], "exit") == 0)
		ft_exit(commands, shell);
}

void	execute_command(t_command *current, t_shell *shell)
{
	signal(SIGQUIT, SIG_DFL);
	if (!current->cmd_name[0])
	{
		shell->exit_status = 0;
		free_and_exit_shell(shell, shell->exit_status);
	}
	if (current->is_builtin == true)
	{
		exec_builtin(current, shell);
		free_and_exit_shell(shell, shell->exit_status);
	}
	else
	{
		shell->cmd_path = get_cmd_path(current->cmd_name[0], shell);
		if (!shell->cmd_path)
		{
			write_error(current->cmd_name[0], "command not found");
			shell->exit_status = 127;
			free_and_exit_shell(shell, shell->exit_status);
		}
		execve(shell->cmd_path, current->cmd_name, shell->env);
		perror(shell->cmd_path);
		if (shell && shell->cmd_path)
			free(shell->cmd_path);
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

void	handle_child(t_command *current, t_shell *shell, int prev_fd)
{
	if (current->redirections)
		open_and_redirect_fd(current, shell);
	has_no_filename(current, shell, prev_fd);
	execute_command(current, shell);
}

int	executer(t_shell *shell)
{
	t_command	*current;
	int			prev_fd;

	if (shell == NULL || shell->commands == NULL)
		return (-1);
	current = shell->commands;
	prev_fd = 0;
	if (!current->next && current->is_builtin == true && !current->redirections)
		exec_builtin(current, shell);
	else
	{
		while (current)
		{
			pipe_and_fork(current, shell);
			if (shell->last_pid == 0)
				handle_child(current, shell, prev_fd);
			else
				prev_fd = handle_parent(current, shell, prev_fd);
			current = current->next;
		}
	}
	wait_commands(shell);
	return (shell->exit_status);
}
