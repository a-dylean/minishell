#include "../includes/minishell.h"

void	exit_shell(t_shell *shell, int exit_code)
{
	if (shell)
	{
	    // close_fds also here
		free_shell(shell);
	}
	exit(exit_code);
}

void free_shell(t_shell *shell)
{
    if (shell)
    {
        if (shell->input)
        {
            free(shell->input);
            shell->input = NULL;
        }
        if (shell->tokens)
            free_tokens(&(shell->tokens));
        if (shell->commands)
            free_commands(&(shell->commands));
        // if (shell->env)
        //     free_env((shell->env_head));
    }
}