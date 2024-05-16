/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:59:27 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/15 15:47:52 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_fds(t_token *redirections, t_shell *shell)
{
	if (redirections->type == GREAT || redirections->type == GREATGREAT)
	{
		get_fd_out(redirections, shell);
		get_fd_in(redirections, shell);
	}
	else
	{
		get_fd_in(redirections, shell);
		get_fd_out(redirections, shell);
	}
}

void	open_and_redirect_fd(t_command *current, t_shell *shell)
{
	get_fds(current->redirections, shell);
	if (shell->infile_fd != -2)
	{
		if (dup2(shell->infile_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			shell->exit_status = 1;
			free_and_exit_shell(shell, shell->exit_status);
		}
		close(shell->infile_fd);
	}
	if (shell->outfile_fd != -2)
	{
		if (dup2(shell->outfile_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			shell->exit_status = 1;
			free_and_exit_shell(shell, shell->exit_status);
		}
		close(shell->outfile_fd);
	}
	if (shell->heredoc && !current->next)
		unlink_heredoc(shell);
}

/*if the command has no specified infile or outfile, it is redirected*/
void	has_no_filename(t_command *current, t_shell *shell, int prev_fd)
{
	if (prev_fd != 0 && shell->infile_fd == -2)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			shell->exit_status = 1;
			free_and_exit_shell(shell, shell->exit_status);
		}
		close(prev_fd);
	}
	if (current->next && shell->outfile_fd == -2)
	{
		if (dup2(shell->pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			shell->exit_status = 1;
			free_and_exit_shell(shell, shell->exit_status);
		}
	}
	if (shell->pipe_fd[0] != -2)
		close(shell->pipe_fd[0]);
	if (shell->pipe_fd[1] != -2)
		close(shell->pipe_fd[1]);
}
