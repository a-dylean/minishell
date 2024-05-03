/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:43:15 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/03 16:20:50 by jlabonde         ###   ########.fr       */
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
	while ((line = readline("> ")) != NULL)
	{	
		if (ft_strcmp(line, redirections->next->value) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
}

int	check_if_other_heredoc(t_token *current)
{
	t_token	*tmp;

	tmp = current->next;
	while (tmp)
	{
		if (tmp->type == LESSLESS)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	handle_heredoc(t_token *redirections, t_shell *shell)
{
	t_token	*current;

	current = redirections;
	while (current)
	{
		if (current->type == LESSLESS && check_if_other_heredoc(current) == 0)
		{
			if (shell->heredoc)
				free(shell->heredoc);
			shell->heredoc = create_filename();
			create_heredoc(current, shell);
			if (!shell->heredoc)
				return ;
		}
		current = current->next;
	}
}