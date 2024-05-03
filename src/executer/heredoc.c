/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:43:15 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/03 15:12:20 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	handle_heredoc(t_token *redirections, t_shell *shell)
// {
// 	(void)shell;
// 	char *line;
// 	int tmp_fd = open("tmp_heredoc", O_RDWR | O_CREAT, 0666);
// 	while ((line = readline("> ")) != NULL)
// 	{
// 		if (strcmp(line, redirections->next->value) == 0)
// 			break;
// 		write(tmp_fd, line, strlen(line));
// 		write(tmp_fd, "\n", 1);
// 	}
//     close(tmp_fd);
//     tmp_fd = open("tmp_heredoc", O_RDONLY);
// 	// dup2(tmp_fd, STDIN_FILENO);
// 	close(tmp_fd);
// }

char	*create_filename(void)
{
	char	*temp_file;
	int		fd;

	temp_file = ft_strjoin("/tmp/minishell_heredoc_", ft_itoa(getpid())); // might have to change, since we can have multiple heredoc in the same PID
	if (!temp_file)
	{
		perror("ft_strjoin");
		return NULL;
	}
	fd = open(temp_file, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
	{
		free(temp_file);
		perror("open");
		return NULL;
	}
	close(fd);
	return (temp_file);
}

void	create_heredoc(t_token *redirections, t_shell *shell)
{
	int		fd;
	char	*line;

	fd = open(shell->heredoc, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	while ((line = readline("> ")) != NULL && ft_strcmp(line, redirections->next->value) != 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
}

void	handle_heredoc(t_token *redirections, t_shell *shell)
{
	t_token	*current;

	current = redirections;
	while (current)
	{
		if (current->type == LESSLESS)
		{
			if (shell->heredoc)
				free(shell->heredoc);
			shell->heredoc = create_filename();
			create_heredoc(redirections, shell);
			if (!shell->heredoc)
				return ;
		}
		current = current->next;
	}
}