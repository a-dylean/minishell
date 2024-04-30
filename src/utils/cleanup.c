#include "../includes/minishell.h"

void free_shell(t_shell *shell)
{
    if (shell && shell->input)
    {
        free(shell->input);
        shell->input = NULL;
    }
    if (shell && shell->tokens)
        free_tokens(&shell->tokens);
    if (shell && shell->commands)
        free_commands(&shell->commands);
}

void clear_shell_history(t_shell *shell)
{
   (void)shell;
    rl_clear_history();
}