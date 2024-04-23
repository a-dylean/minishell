/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:28:00 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/23 11:30:28 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_shell(t_shell *shell, char **env)
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
	}
	shell->exit_status = 0;
	shell->heredoc = NULL;
	shell->std_fds[0] = dup(STDIN_FILENO);
	shell->std_fds[1] = dup(STDOUT_FILENO);
}