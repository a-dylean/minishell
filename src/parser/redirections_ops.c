/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_ops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:55:53 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/23 17:20:03 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	handle_redirections(t_token *tokens, t_command *command)
{
	t_token	*temp;
	t_token	*redirections;
	t_token	*next;

	redirections = NULL;
	temp = tokens;
	next = NULL;
	if (temp->type == PIPE && temp->next)
		temp = temp->next;
	while (temp && temp->type != PIPE)
	{
		if (temp->next && temp->type >= LESS && temp->type <= LESSLESS)
		{
			next = temp->next->next;
			add_token_back(&redirections, create_token(temp->value, temp->type));
			add_token_back(&redirections, create_token(temp->next->value,
			 		temp->next->type));
			temp = next;
		}
		else
			temp = temp->next;
	}
	command->redirections = redirections;
	// HANDLE FREE MAYBE AT EXIT free_tokens(&redirections);
}
