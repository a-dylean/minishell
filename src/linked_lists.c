/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:04:54 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/19 14:37:39 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*create_token(char *value, int type)
{
	t_token	*token;
	static int id = 0;

	token = malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->id = id++;
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token_back(t_token **tokens, t_token *new_node)
{
	t_token *current;

	if (!new_node)
		return ;
	if (*tokens == NULL)
		*tokens = new_node;
	else
	{
		current = *tokens;
		while (current->next)
			current = current->next;
		current->next = new_node;
		new_node->prev = current;
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	*temp;
	t_token	*current;

	if (!*tokens)
		return ;
	current = *tokens;
	while (current)
	{
		temp = current->next;
		free(current->value);
		free(current);
		current = temp;
	}
	*tokens = NULL;
}

t_token	*clear_one(t_token **tokens)
{
	if ((*tokens) && (*tokens)->value)
	{
		free((*tokens)->value);
		(*tokens)->value = NULL;
	}
	return (NULL);
}

void	del_first(t_token **tokens)
{
	t_token	*node;

	node = *tokens;
	*tokens = node->next;
	clear_one(&node);
	if (*tokens)
		(*tokens)->prev = NULL;
}

int	len_list(t_token *list)
{
	t_token	*current;
	int		i;

	current = list;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}
