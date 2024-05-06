/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:43:15 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/06 15:33:55 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_filename(t_shell *shell)
{
	char	*temp_file;
	int		fd;
	static int i = 0;

	temp_file = ft_strjoin("/tmp/minishell_heredoc_", ft_itoa(getpid()) + i);
	if (!temp_file)
	{
		perror("ft_strjoin");
		return ;
	}
	fd = open(temp_file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	i++;
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
	t_token	tmp = {0};

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
		tmp.value = line;
		if (redirections->next->quotes_status == NONE)
			perform_expansion(&tmp, shell);
		if (tmp.value)
			write(fd, tmp.value, ft_strlen(tmp.value));
		write(fd, "\n", 1);
		free(line);
		if (tmp.value != line)
		{
			free(tmp.value);
			tmp.value = NULL;
		}
	}
	if (line)
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