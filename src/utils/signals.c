/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:08:57 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/30 15:12:46 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_sigint(int signum)
{
	(void)signum;
	g_exit_code = 130;
	ft_putstr_fd("\n", STDOUT_FILENO);
	close(STDIN_FILENO);
}

/* function that resets the readline user input prompt
for interactive signal handling */
void	catch_sigint(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_code = 130;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ignore_signals(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, catch_sigint);
}
