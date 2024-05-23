/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:16:29 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/23 15:34:54 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	invalid_type_syntax_error(t_token *token, t_shell *shell)
{
	if (token->value[0] == '>' && token->value[1] == '>'
		&& ft_strlen(token->value) >= 4)
		return (syntax_error_in_token(">>", shell));
	else if (token->value[0] == '<' && token->value[1] == '<'
		&& ft_strlen(token->value) >= 6)
		return (syntax_error_in_token("<<<", shell));
	else if (token->value[0] == '<' && token->value[1] == '<'
		&& ft_strlen(token->value) >= 4)
		return (syntax_error_in_token("<<", shell));
	else if (token->value[0] == '>')
		return (syntax_error_in_token(">", shell));
	else if (token->value[0] == '<')
		return (syntax_error_in_token("<", shell));
	else if (token->value && token->next && token->next->value
		&& token->next->next && token->next->next->value)
	{
		if (!ft_strcmp(token->value, "|") && !ft_strcmp(token->next->value, "|")
			&& !ft_strcmp(token->next->next->value, "|"))
			return (syntax_error_in_token("||", shell));
	}
	if (token->value[0] == '|')
		return (syntax_error_in_token("|", shell));
	return (0);
}

int	check_syntax(t_token *tokens, t_shell *shell)
{
	t_token	*tmp;
	int		heredoc;
	int		ret;

	heredoc = 0;
	tmp = tokens;
	ret = 0;
	while (tmp)
	{
		if (tmp->type == DELIMITER)
		{
			if (heredoc == 0)
				ret = handle_heredoc(tmp, shell, heredoc);
			else
				handle_heredoc(tmp, shell, heredoc);
			heredoc++;
		}
		if (heredoc == 0)
		{
			if (tmp->type == -1)
				return (invalid_type_syntax_error(tmp, shell));
			else if (tmp->type == PIPE && (!tmp->prev || !tmp->next
					|| tmp->prev->type == PIPE || tmp->next->type == PIPE))
				return (invalid_type_syntax_error(tmp, shell));
			else if (tmp->type >= LESS && tmp->type <= LESSLESS)
			{
				if (!tmp->next)
					return (syntax_error_in_token("newline", shell));
				else if (tmp->next->type != FILENAME
					&& tmp->next->type != DELIMITER)
					return (syntax_error_in_token(tmp->next->value, shell));
			}
		}
		tmp = tmp->next;
	}
	return (ret);
}
