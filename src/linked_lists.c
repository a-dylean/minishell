/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:04:54 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/11 14:22:35 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*ft_get_last_node(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_add_node_back(t_token **tokens, t_token *new_node)
{
	t_token	*temp;

	if (!new_node)
		return ;
	if (*tokens && new_node)
	{
		temp = ft_get_last_node(*tokens);
		temp->next = new_node;
		new_node->next = NULL;
	}
	else
	{
		*tokens = new_node;
		(*tokens)->next = NULL;
	}
}

void	free_stack(t_token **tokens)
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