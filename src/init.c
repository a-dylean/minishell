/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:28:00 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/07 14:21:01 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int init_shell(t_shell *shell, char **env)
{
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
	// shell->tokens = *init_tokens();
	// shell->commands = *init_commands();
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->last_pid = -2;
	shell->infile_fd = -2;
	shell->outfile_fd = -2;
	shell->pipe_fd[0] = -2;
	shell->pipe_fd[1] = -2;
	shell->prev_fd = 0;
	shell->exit_status = 0;
	shell->prev_dir = NULL;
	shell->cur_dir = NULL;
	shell->heredoc = NULL;
	return (EXIT_SUCCESS);
}

