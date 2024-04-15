/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens_ops.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:52:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/15 13:02:44 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*remove_token_by_id(t_token *tokens, int id)
{
	t_token	*temp;
	t_token	*current;

	// if (tokens == NULL)
	// 	return (NULL);
	if (tokens->id == id)
	{
		temp = tokens->next;
		free(tokens);
		return (temp);
	}
	current = tokens;
	while (current->next != NULL)
	{
		if (current->next->id == id)
		{
			temp = current->next->next;
			free(current->next);
			current->next = temp;
			if (temp != NULL)
				temp->prev = current;
			break ;
		}
		current = current->next;
	}
	return (tokens);
}

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
