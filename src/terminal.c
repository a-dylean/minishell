/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:43:00 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/30 14:43:56 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_exit_code;

int valid_quotes(char *str)
{
    int i;
	int in_single_quote;
    int in_double_quote;
    
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
    return !(in_single_quote || in_double_quote);
}

int	trim_and_verify_buffer(char *buffer)
{
	buffer = ft_strtrim(buffer, " ");
	if (!buffer || buffer[0] == '\0')
	{
		free(buffer);
		return (EXIT_FAILURE);
	}
	else if (!valid_quotes(buffer))
	{
		printf("Error: invalid quotes\n");
		free(buffer);
		return (EXIT_FAILURE);
	}
	add_history(buffer);
	free(buffer);
	return (EXIT_SUCCESS);
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

int non_interactive_behaviour(t_shell *shell, char *command)
{
	(void)shell;
	(void)command;
	printf("Non interactive behaviour\n");
	return (EXIT_SUCCESS);
}

int	minishell_loop(t_shell *shell)
{
	char		*buffer;
	t_token		**tokens;
	t_command	*commands;

	buffer = NULL;
	commands = NULL;
	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, SIG_IGN);
	while ((buffer = readline(PROMPT)))
	{
		if (trim_and_verify_buffer(buffer))
			continue ;
		tokens = init_tokens();
		if (!tokens)
			return (EXIT_FAILURE); // we need to free stuff here
		lexer(buffer, tokens);
		if (!check_syntax(*tokens))
			commands = parser(*tokens, shell);
		if (!commands)
		{
			// free the tokens list
			return (EXIT_FAILURE);
		}
		executer(commands, shell);
		free_in_terminal(tokens, buffer);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
