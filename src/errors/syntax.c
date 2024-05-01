/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:16:29 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/19 16:13:54 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// modify for readabilty, split into smaller functions
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
		if (tmp->type == PIPE && (!tmp->prev || !tmp->next))
			return (syntax_error_in_token("|"));
		if (tmp->type >= LESS && tmp->type <= LESSLESS)
		{
			if (!tmp->next)
				return (syntax_error_in_token("newline"));
		}
		tmp = tmp->next;
	}
	return (0);
}
