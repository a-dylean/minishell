/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:28:00 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/30 14:12:10 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_shell(t_shell *shell, char **env)
{
	shell->env_list = init_env(env);
	if (shell->env_list == NULL)
		return (EXIT_FAILURE);
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->last_pid = -2;
	shell->infile_fd = -2;
	shell->outfile_fd = -2;
	shell->pipe_fd[0] = -2;
	shell->pipe_fd[1] = -2;
	shell->exit_status = 0;
	shell->heredoc = NULL;
	shell->old_stdin = -1;
	return (EXIT_SUCCESS);
}
