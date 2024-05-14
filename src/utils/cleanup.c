#include "../includes/minishell.h"

void	free_and_exit_shell(t_shell *shell, int exit_code)
{
	if (shell)
	{
		free_shell(shell);
		if (shell->env && shell->env_head)
			free_env((shell->env_head));
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
