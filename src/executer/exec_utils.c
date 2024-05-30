/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:48:58 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/30 14:21:17 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_if_other_heredoc(t_token *current)
{
	t_token	*tmp;

	tmp = current->next;
	while (tmp)
	{
		if (tmp->type == LESSLESS)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	write_line_to_heredoc(int fd, char *tmp, t_shell *shell,
		int quotes_status)
{
	if (quotes_status == 0)
		tmp = expander(tmp, shell);
	if (tmp)
		write(fd, tmp, ft_strlen(tmp));
	write(fd, "\n", 1);
	if (tmp)
		free(tmp);
}

void	free_line(char *line, t_token *tmp)
{
	free(line);
	if (tmp->value != line)
	{
		free(tmp->value);
		tmp->value = NULL;
	}
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

void	wait_commands(t_shell *shell)
{
	signal(SIGINT, SIG_IGN);
	while (errno != ECHILD)
	{
		if (wait(&shell->wstatus) == shell->last_pid)
		{
			if (WIFEXITED(shell->wstatus))
				shell->exit_status = WEXITSTATUS(shell->wstatus);
			else
			{
				shell->exit_status = 128 + WTERMSIG(shell->wstatus);
				if (shell->exit_status == 131)
					ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				else if (shell->exit_status == 139)
					ft_putstr_fd("Segmentation fault (core dumped)\n",
						STDERR_FILENO);
			}
			if (shell->exit_status == 130)
				ft_putstr_fd("\n", STDERR_FILENO);
		}
	}
	if (g_exit_code == 130)
		shell->exit_status = 130;
}
