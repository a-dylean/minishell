/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:39:38 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/22 14:12:15 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	duplicate_fd(int fd, int new_fd, t_shell *shell, int exit_status)
{
	if (dup2(fd, new_fd) == -1)
	{
		perror("dup2");
		shell->exit_status = exit_status;
		free_and_exit_shell(shell, shell->exit_status);
	}
}

void	close_fds(t_shell *shell)
{
	if (shell->infile_fd >= 0)
		close(shell->infile_fd);
	if (shell->outfile_fd >= 0)
		close(shell->outfile_fd);
}

void	close_pipe_fds(t_shell *shell)
{
	if (shell->pipe_fd[0] != -2)
		close(shell->pipe_fd[0]);
	if (shell->pipe_fd[1] != -2)
		close(shell->pipe_fd[1]);
}
