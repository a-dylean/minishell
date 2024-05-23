/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:43:15 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/23 15:34:13 by jlabonde         ###   ########.fr       */
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

void	create_heredoc(char *delimiter, t_shell *shell, int quote_status)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(shell->heredoc, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		tmp = line;
		write_line_to_heredoc(fd, tmp, shell, quote_status);
		line = readline("> ");
	}
	if (line)
		free(line);
	close(fd);
}

int	case_heredoc_syntax(t_token *tokens, t_shell *shell)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == -1)
			return (invalid_type_syntax_error(tmp, shell));
		else if (tmp->type == PIPE && (!tmp->prev || !tmp->next
				|| tmp->prev->value[0] == '|' || tmp->next->value[0] == '|'))
			return (invalid_type_syntax_error(tmp, shell));
		else if (tmp->type >= LESS && tmp->type <= LESSLESS)
		{
			if (!tmp->next)
				return (syntax_error_in_token("newline", shell));
			else if (tmp->next->type != FILENAME
				&& tmp->next->type != DELIMITER)
				return (syntax_error_in_token(tmp->next->value, shell));
		}
		tmp = tmp->next;
	}
	return (0);
}

int	handle_heredoc(t_token *tmp, t_shell *shell, int option)
{
	int	ret;

	ret = 0;
	if (option == 0)
		ret = case_heredoc_syntax(shell->tokens, shell);
	if (shell->heredoc)
		free(shell->heredoc);
	create_filename(shell);
	create_heredoc(tmp->value, shell, tmp->quotes_status);
	if (!shell->heredoc)
		return (1);
	return (ret);
}
