/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:52:49 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/17 16:22:06 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_and_exit_shell(t_shell *shell, int exit_code)
{
	if (shell)
	{
		free_shell(shell);
		if (shell->env_list)
			free_env((shell->env_list));
	}
	exit(exit_code);
}

void	free_shell(t_shell *shell)
{
	if (shell)
	{
		if (shell->input)
		{
			free(shell->input);
			shell->input = NULL;
		}
		if (shell->heredoc)
		{
			free(shell->heredoc);
			shell->heredoc = NULL;
		}
		if (shell->prev_dir)
		{
			free(shell->prev_dir);
			shell->prev_dir = NULL;
		}
		if (shell->cur_dir)
		{
			free(shell->cur_dir);
			shell->cur_dir = NULL;
		}
		if (shell->tokens)
			free_tokens(&(shell->tokens));
		if (shell->commands)
			free_commands(&(shell->commands));
	}
}
