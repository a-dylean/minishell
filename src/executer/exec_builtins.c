/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:00:46 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/02 14:29:10 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exec_single_builtin(t_command *commands, t_shell *shell)
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

void	fd_in(t_token *redirections, t_shell *shell)
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
			shell->exit_status = 1;
			return ;
		}
		current = current->next;
	}
}

void	fd_out(t_token *redirections, t_shell *shell)
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
			shell->exit_status = 1;
			return ;
		}
		current = current->next;
	}
}
static void	handle_builtins_redirections(t_command *command, t_shell *shell)
{
	fd_in(command->redirections, shell);
	fd_out(command->redirections, shell);
	if (shell->infile_fd != -2 && shell->infile_fd != -1)
	{
		if (dup2(shell->infile_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	if (shell->outfile_fd != -2 && shell->infile_fd != -1)
	{
		if (dup2(shell->outfile_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
}

void	handle_single_builtin(t_command *commands, t_shell *shell)
{
	if (commands->redirections)
		handle_builtins_redirections(commands, shell);
	exec_single_builtin(commands, shell);
}
