/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:59:27 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/26 16:18:54 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	open_and_redirect_fd(t_command *current, t_shell *shell)
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
/*if the command has no specified infile or outfile, it is redirected*/
void	has_no_filename(t_command *current, t_shell *shell, int prev_fd)
{
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
}
