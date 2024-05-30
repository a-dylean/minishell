/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:52:49 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/30 15:16:59 by jlabonde         ###   ########.fr       */
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
	rl_clear_history();
	exit(exit_code);
}

void	free_shell(t_shell *shell)
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

void	free_tokens(t_token **tokens)
{
	t_token	*temp;
	t_token	*current;

	if (!*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		temp = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = temp;
	}
	*tokens = NULL;
}

void	free_commands(t_command **commands)
{
	t_command	*temp;
	t_command	*current;

	if (!*commands)
		return ;
	current = *commands;
	while (current)
	{
		temp = current->next;
		if (current->cmd_name)
			free_array(current->cmd_name);
		free_tokens(&(current->redirections));
		free(current);
		current = temp;
	}
	*commands = NULL;
}
