/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:43:00 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/17 14:28:05 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_quotes(char *str)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (str[i])
	{
		if (str[i] == S_QUOTE && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == D_QUOTE && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	return (!(in_single_quote || in_double_quote));
}

/* function that resets the readline user input prompt
for interactive signal handling */

void	catch_sigint(int signum)
{
	(void)signum;
	g_exit_code = signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	minishell_loop(t_shell *shell)
{
	while (1)
	{
		signal(SIGINT, catch_sigint);
		signal(SIGQUIT, SIG_IGN);
		shell->input = readline(PROMPT);
		if (!shell->input)
            free_and_exit_shell(shell, 1);
		if (lexer(shell) == EXIT_SUCCESS && parser(shell) == EXIT_SUCCESS)
			g_exit_code = executer(shell);
		else
			g_exit_code = 1;
		free_shell(shell);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
