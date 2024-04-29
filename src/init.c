/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:28:00 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/26 17:05:58 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int init_shell(t_shell *shell, char **env)
{
	(void)env;
	if (getenv("USER") == NULL)
		// initialize shell with no env
		printf("USER not found in environment\n");
	else
	{
		shell->envless = 0;
		shell->env_head = init_env(env);
		shell->user_name = getenv("USER");
		shell->env = env;
	}
	shell->infile_fd = -2;
	shell->outfile_fd = -2;
	shell->prev_fd = 0;
	shell->exit_status = 0;
	shell->heredoc = NULL;
	shell->std_fds[0] = dup(STDIN_FILENO);
	shell->std_fds[1] = dup(STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

t_token **init_tokens(void)
{
	t_token **tokens;

	tokens = (t_token **)malloc(sizeof(t_token));
	if (!tokens)
		return (NULL);
	*tokens = NULL;
	return (tokens);
}
