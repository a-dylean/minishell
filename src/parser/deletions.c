/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:18:34 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/06 12:38:40 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* functions in this file are no longer used - double check ! */

t_token	*remove_first_pipe(t_token *tokens, int id)
{
	t_token	*temp;

	if (id == 0 && tokens->type == PIPE)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp);
	}
	return (tokens);
}

t_token	*remove_pipes(t_token *tokens, int id)
{
	t_token	*temp;
	int		i;

	i = 0;
	if (id == 0 && tokens->type == PIPE)
		return (remove_first_pipe(tokens, id));
	while (tokens && i != id)
	{
		if (tokens->type != PIPE)
		{
			temp = tokens;
			tokens = tokens->next;
			free(temp);
			i++;
		}
		else
		{
			temp = tokens;
			tokens = tokens->next;
			free(temp);
		}
	}
	if (tokens == NULL)
		return (NULL);
	return (tokens);
}

void	delete_next_type(t_token **tokens, int type)
{
	t_token *node;
	t_token *prev;
	t_token *start;

	start = *tokens;
	node = start;
	if ((*tokens)->type == type)
	{
		del_first(tokens);
		return ;
	}
	while (node && node->type != type)
	{
		prev = node;
		node = node->next;
	}
	if (node)
		prev->next = node->next;
	else
		prev->next = NULL;
	if (prev->next)
		prev->next->prev = prev;
	clear_one(&node);
	*tokens = start;
}
