/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_ops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:55:53 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/19 17:22:46 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	**init_redirections(void)
{
	t_token	**redirections;

	redirections = (t_token **)malloc(sizeof(t_token));
	if (!redirections)
		exit(EXIT_FAILURE);
	*redirections = NULL;
	return (redirections);
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

void	handle_redirections(t_token *tokens, t_command *command, t_command **commands)
{
	t_token	*temp;
	t_token	**redirections;
	t_token	*next;

	redirections = init_redirections();
	temp = tokens;
	next = NULL;
	if ((*commands) && temp->type == PIPE && temp->next)
		temp = temp->next;
	while (temp && temp->type != PIPE)
	{
		if (temp->next && temp->type >= LESS && temp->type <= LESSLESS)
		{
			next = temp->next->next;
			add_token_back(redirections, create_token(temp->value, temp->type));
			add_token_back(redirections, create_token(temp->next->value,
			 		temp->next->type));
			temp = next;
		}
		else
			temp = temp->next;
	}
	command->redirections = *redirections;
	//free(redirections);
}
