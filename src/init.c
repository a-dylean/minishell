/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:28:00 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/30 18:02:00 by atonkopi         ###   ########.fr       */
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
	shell->infile_fd = -2;
	shell->outfile_fd = -2;
	shell->prev_fd = 0;
	shell->exit_status = 0;
	shell->heredoc = NULL;
	shell->std_fds[0] = dup(STDIN_FILENO);
	shell->std_fds[1] = dup(STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

