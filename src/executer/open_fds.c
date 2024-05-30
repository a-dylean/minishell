/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:46:13 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/30 11:34:08 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	get_file_as_fd_in(t_token *redirections, t_shell *shell)
{
	t_token	*current;

	current = redirections;
	while (current)
	{
		if (current->next && (current->next->type == FILENAME))
		{
			if (current->type == LESS)
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
			free_and_exit_shell(shell, shell->exit_status);
		}
		current = current->next;
	}
}

void	get_fd_in(t_token *redirections, t_shell *shell)
{
	if (shell->heredoc && redirections->type == LESSLESS)
	{
		if (shell->infile_fd != -2)
			close(shell->infile_fd);
		shell->infile_fd = open(shell->heredoc, O_RDONLY);
	}
	get_file_as_fd_in(redirections, shell);
}

static void	open_outfile(char *filename, t_shell *shell, int flags)
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
			shell->exit_status = 1;
			free_and_exit_shell(shell, shell->exit_status);
		}
		current = current->next;
	}
}
