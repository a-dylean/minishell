/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens_ops.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:52:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/19 14:40:44 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_tokens_before_pipe(t_token *tokens)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = tokens;
	if (temp->type == PIPE)
		temp = temp->next;
	while (temp && temp->type != PIPE)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int	no_pipe_in_list(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->type == PIPE)
			return (0);
		temp = temp->next;
	}
	return (1);
}
