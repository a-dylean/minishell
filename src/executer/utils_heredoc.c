/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:59:58 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/15 16:00:27 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	write_line_to_heredoc(int fd, t_token *tmp,
			t_shell *shell, t_token *redirections)
{
	if (redirections->next->quotes_status == NONE)
		perform_expansion(tmp, shell);
	if (tmp->value)
		write(fd, tmp->value, ft_strlen(tmp->value));
	write(fd, "\n", 1);
}

void	free_line(char *line, t_token *tmp)
{
	free(line);
	if (tmp->value != line)
	{
		free(tmp->value);
		tmp->value = NULL;
	}
}
