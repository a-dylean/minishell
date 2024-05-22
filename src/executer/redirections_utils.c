#include "../../includes/minishell.h"

void	duplicate_fd(int fd, int new_fd, t_shell *shell, int exit_status)
{
	if (dup2(fd, new_fd) == -1)
	{
		perror("dup2");
		shell->exit_status = exit_status;
		free_and_exit_shell(shell, shell->exit_status);
	}
}
