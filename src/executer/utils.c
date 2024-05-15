/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:48:58 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/15 16:26:47 by jlabonde         ###   ########.fr       */
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

void	write_line_to_heredoc(int fd, t_token *tmp,
			t_shell *shell, t_token *redirections)
{
	if (redirections->next->quotes_status == NONE)
		perform_expansion(tmp, shell);
	if (tmp->value)
		write(fd, tmp->value, ft_strlen(tmp->value));
	write(fd, "\n", 1);
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
	if (current->redirections)
		handle_heredoc(current->redirections, shell);
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
				shell->exit_status = 128 + WTERMSIG(shell->wstatus);
		}
	}
	signal(SIGINT, catch_sigint);
}
