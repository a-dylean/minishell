/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:04:54 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/10 13:24:39 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*create_token(char *value, int type)
{
	t_token		*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->quotes_status = 0;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token_back(t_token **tokens, t_token *new_node)
{
	t_token	*current;

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
		if (current->value)
			free(current->value);
		free(current);
		current = temp;
	}
	*tokens = NULL;
}

void	free_commands(t_command **commands)
{
	t_command	*temp;
	t_command	*current;

	if (!*commands)
		return ;
	current = *commands;
	while (current)
	{
		temp = current->next;
		if (current->cmd_name)
			free_array(current->cmd_name);
		free_tokens(&(current->redirections));
		free(current);
		current = temp;
	}
	*commands = NULL;
}
