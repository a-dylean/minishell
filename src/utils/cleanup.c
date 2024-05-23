/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:52:49 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/22 17:44:45 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_and_exit_shell(t_shell *shell, int exit_code)
{
	if (shell)
	{
		free_shell(shell);
		if (shell->env_list)
			free_env((shell->env_list));
	}
	exit(exit_code);
}

void free_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->heredoc)
		{
			free(shell->heredoc);
			shell->heredoc = NULL;
		}
		if (shell->tokens)
			free_tokens(&(shell->tokens));
		if (shell->commands)
			free_commands(&(shell->commands));
	}
}
