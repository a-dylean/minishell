/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:43:15 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/16 17:47:35 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unlink_heredoc(t_shell *shell)
{
	if (unlink(shell->heredoc) == -1)
	{
		perror("unlink");
		exit(EXIT_FAILURE);
	}
}

void	create_filename(t_shell *shell)
{
	char		*temp_file;
	int			fd;
	char		*temp_num;

	temp_num = ft_itoa(getpid() + 1);
	temp_file = ft_strjoin("/tmp/minishell_heredoc_", temp_num);
	free(temp_num);
	if (!temp_file)
	{
		perror("ft_strjoin");
		free(temp_file);
		return ;
	}
	fd = open(temp_file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		free(temp_file);
		perror("open");
		return ;
	}
	close(fd);
	shell->heredoc = temp_file;
}

void	create_heredoc(t_token *redirections, t_shell *shell)
{
	int		fd;
	char	*line;
	t_token	tmp;

	ft_memset(&tmp, 0, sizeof(t_token));
	fd = open(shell->heredoc, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strcmp(line, redirections->next->value) == 0)
			break ;
		tmp.value = line;
		write_line_to_heredoc(fd, &tmp, shell, redirections);
		// free_line(line, &tmp);
		line = readline("> ");
	}
	if (line)
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
			create_filename(shell);
			create_heredoc(current, shell);
			if (!shell->heredoc)
				return ;
		}
		current = current->next;
	}
}
