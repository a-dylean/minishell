/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections_ops.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:55:53 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/15 13:02:17 by atonkopi         ###   ########.fr       */
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

// function that adds redirections (array of tokens) to the command struct
// and then removes them from the tokens list
void	handle_redirections(t_token *tokens, t_command *command)
{
	t_token	*temp;
	t_token	**redirections;
	t_token	*next;

	redirections = init_redirections();
	temp = tokens;
	while (temp)
	{
		if (temp->type >= LESS && temp->type <= LESSLESS)
		{
			handle_redirection_token(temp, redirections, &next, &tokens);
			temp = next;
			break ;
		}
		temp = temp->next;
	}
	command->redirections = *redirections;
}

void	handle_redirection_token(t_token *temp, t_token **redirections,
		t_token **next, t_token **tokens)
{
	add_token_back(redirections, create_token(temp->value, temp->type));
	if (temp->next)
	{
		*next = temp->next->next;
		add_token_back(redirections, create_token(temp->next->value,
				temp->next->type));
		*tokens = remove_token_by_id(*tokens, temp->next->id);
	}
	else
		*next = NULL;
	*tokens = remove_token_by_id(*tokens, temp->id);
}