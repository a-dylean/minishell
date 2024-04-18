/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections_ops.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:55:53 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/18 13:02:23 by jlabonde         ###   ########.fr       */
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
// void	handle_redirections(t_token *tokens, t_command *command)
// {
// 	t_token	*temp;
// 	t_token	**redirections;
// 	t_token	*next;

// 	redirections = init_redirections();
// 	temp = tokens;
// 	next = NULL;
// 	if (temp->type == PIPE && temp->next)
// 		temp = temp->next;
// 	while (temp && temp->type != PIPE)
// 	{
		
// 		printf("temp->value: %s\n", temp->value);
// 		if (temp->type >= LESS && temp->type <= LESSLESS)
// 		{
// 			handle_redirection_token(temp, redirections, &next, &tokens);
// 			// temp = tokens;
// 			temp = next;
// 			//break ;
// 		}
// 		else
// 			temp = temp->next;
// 	}
// 	command->redirections = *redirections;
// 	//free(redirections);
// }

void	delete_next_token(t_token **tokens, int type)
{
	t_token *node;
	t_token *prev;
	t_token *start;

	start = *tokens;
	node = start;
	if ((*tokens)->type == type)
	{
		ft_lexerdel_first(tokens);
		return ;
	}
	while (node && node->type != type)
	{
		prev = node;
		node = node->next;
		// node->prev = prev;
	}
	if (node)
		prev->next = node->next;
	else
		prev->next = NULL;
	if (prev->next)
		prev->next->prev = prev;
	ft_lexerclear_one(&node);
	*tokens = start;
}

void	handle_redirections(t_token *tokens, t_command *command)
{
	t_token	*temp;
	t_token	**redirections;
	t_token	*next;

	redirections = init_redirections();
	temp = tokens;
	next = NULL;
	if (temp->type == PIPE && temp->next)
		temp = temp->next;
	while (temp && temp->type != PIPE)
	{
		if (temp->next && temp->type >= LESS && temp->type <= LESSLESS)
		{
			next = temp->next->next;
			add_token_back(redirections, create_token(temp->value, temp->type));
			add_token_back(redirections, create_token(temp->next->value,
			 		temp->next->type));
			// t_token *current = *redirections;
			// while(current)
			// {
			// 	printf("current->value: %s\n", current->value);
				
			// 	current = current->next;
			// }
			// printf("temp->value: %s\n", temp->value);
			// printf("\n");
			// // t_token *current = tokens;
			// // while (current)
			// // {
			// // 	printf("current->value: %s\n", current->value);
			// // 	current = current->next;
			// // }
			// printf("\n");
			//delete_next_token(&tokens, temp->type);
			//delete_next_token(&tokens, temp->next->type);
			// current = tokens;
			// while (current)
			// {
			// 	printf("after ->value: %s\n", current->value);
			// 	current = current->next;
			// }
			// printf("\n");
			temp = next;
		}
		else
			temp = temp->next;
	}
	command->redirections = *redirections;
	//free(redirections);
}


void	handle_redirection_token(t_token *temp, t_token **redirections,
		t_token **next, t_token **tokens)
{
	if (temp->next)
	{
		*next = temp->next->next;
		add_token_back(redirections, create_token(temp->value, temp->type));
		add_token_back(redirections, create_token(temp->next->value,
				temp->next->type));
		t_token *current = *tokens;
		while (current)
		{
			printf("current->value: %s\n", current->value);
			current = current->next;
		}
		//*tokens = remove_token_by_id(*tokens, temp->next->id);
		delete_next_token(tokens, temp->type);
		delete_next_token(tokens, temp->next->type);
		current = *tokens;
		while (current)
		{
			printf("after ->value: %s\n", current->value);
			current = current->next;
		}
	}
	else
		*next = NULL;
	// if (*tokens)
	// {
	// 	if ((*tokens)->next)
	// 		delete_next_token(tokens, temp->type);
	// 	else
	// 		(*tokens)->value = NULL;
	// }
}
