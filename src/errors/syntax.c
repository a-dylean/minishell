/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:16:29 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/20 18:52:01 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	invalid_type_syntax_error(t_token *token)
// {
// 	if (token->value[0] == '>' && token->value[1] == '>'
// 		&& ft_strlen(token->value) >= 4)
// 		return (syntax_error_in_token(">>"));
// 	else if (token->value[0] == '<' && token->value[1] == '<'
// 		&& ft_strlen(token->value) >= 4)
// 		return (syntax_error_in_token("<<"));
// 	else if (token->value[0] == '>')
// 		return (syntax_error_in_token(">"));
// 	else if (token->value[0] == '<')
// 		return (syntax_error_in_token("<"));
// 	else if (token->value[0] == '|' && token->value[1] == '|'
// 		&& ft_strlen(token->value) >= 2)
// 		return (syntax_error_in_token("||"));
// 	else if (token->value[0] == '|')
// 		return (syntax_error_in_token("|"));
// 	return (0);
// }

int	check_syntax(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		// if (tmp->type == -1)
		// 	return (syntax_error_in_token(tmp->value));
		if (tmp->type == PIPE && (!tmp->prev || !tmp->next
				|| tmp->next->type == PIPE))
		{
			if (tmp->next && tmp->next->type == PIPE)
				return (syntax_error_in_token("||"));
			return (syntax_error_in_token("|"));
		}
		if (tmp->type >= LESS && tmp->type <= LESSLESS)
		{
			if (!tmp->next)
				return (syntax_error_in_token("newline"));
			else if (tmp->next->type != FILENAME
				&& tmp->next->type != DELIMITER)
				return (syntax_error_in_token(tmp->next->value));
		}
		tmp = tmp->next;
	}
	return (0);
}
