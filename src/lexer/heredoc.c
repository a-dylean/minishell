/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:43:15 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/30 15:22:06 by jlabonde         ###   ########.fr       */
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
	char	*temp_file;
	int		fd;
	char	*temp_num;

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

void	cleanup_heredoc(int fd, t_shell *shell)
{
	if (fd != -1)
		close(fd);
	close(STDIN_FILENO);
	dup2(shell->old_stdin, STDIN_FILENO);
	close(shell->old_stdin);
}

void	create_heredoc(char *delimiter, t_shell *shell, int quote_status)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(shell->heredoc, O_RDWR | O_CREAT, 0666);
	if (fd == -1)
		return (perror("open"));
	signal(SIGINT, heredoc_sigint);
	while (g_exit_code != 130)
	{	
		line = readline("> ");
		if ((line && ft_strcmp(line, delimiter) == 0))
			break ;
		if (line == NULL)
		{
			if (g_exit_code != 130)
				write_warning(delimiter);
			break ;
		}
		tmp = line;
		write_line_to_heredoc(fd, tmp, shell, quote_status);
	}
	if (line)
		free(line);
	cleanup_heredoc(fd, shell);
}

int	handle_heredoc(t_token *tmp, t_shell *shell, int option)
{
	int	ret;

	ret = 0;
	shell->old_stdin = dup(STDIN_FILENO);
	if (option == 0)
		ret = case_heredoc_syntax(shell->tokens, shell);
	if (shell->heredoc)
		free(shell->heredoc);
	create_filename(shell);
	signal(SIGINT, heredoc_sigint);
	create_heredoc(tmp->value, shell, tmp->quotes_status);
	if (!shell->heredoc)
		return (1);
	return (ret);
}
