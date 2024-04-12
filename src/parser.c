/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:27:28 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/12 16:35:19 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_tokens_before_pipe(t_token *tokens)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = tokens;
	while (temp && temp->type != PIPE)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}
t_token	*ft_lexerclear_one(t_token **lst)
{
	if ((*lst)->value)
	{
		free((*lst)->value);
		(*lst)->value = NULL;
	}
	free(*lst);
	lst = NULL;
	return (NULL);
}

void	ft_lexerdel_first(t_token **lst)
{
	t_token	*node;

	node = *lst;
	*lst = node->next;
	ft_lexerclear_one(&node);
	if (*lst)
		(*lst)->prev = NULL;
}

void	remove_redir_from_tokens(t_token **tokens, int id)
{
	t_token	*node;
	t_token	*prev;
	t_token	*start;

	start = *tokens;
	node = start;
	if ((*tokens)->id == id)
	{
		ft_lexerdel_first(tokens);
		return ;
	}
	while (node && node->id != id)
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
	ft_lexerclear_one(&node);
	*tokens = start;
}

void	remove_cmd_from_tokens(t_token **tokens)
{
	t_token	*temp;
	int		num_of_nodes;

	num_of_nodes = count_tokens_before_pipe(*tokens);
	while (num_of_nodes > 0 && *tokens)
	{
		temp = (*tokens)->next;
		free(*tokens);
		*tokens = temp;
		num_of_nodes--;
	}
}

t_command	*init_command(void)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
		exit(EXIT_FAILURE);
	new_command->cmd_name = NULL;
	new_command->out = NULL;
	new_command->in = NULL;
	new_command->delimiter = NULL;
	new_command->env = NULL;
	return (new_command);
}
// function that returns an array of strings (command) from the tokens list
char	**get_cmd_from_tokens(t_token *tokens)
{
	int		num_tokens;
	int		i;
	t_token	*temp;
	char	**array;

	i = 0;
	temp = tokens;
	num_tokens = count_tokens_before_pipe(tokens);
	array = malloc((num_tokens + 1) * sizeof(char *));
	if (!array)
		exit(EXIT_FAILURE);
	while (temp)
	{
		array[i] = ft_strdup(temp->value);
		temp = temp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
// function that adds redirections (array of tokens) to the command struct
// and then removes them from the tokens list
void	handle_redirections(t_token *tokens, t_command *command)
{
	t_token	*temp;
	// t_token	*current;

	temp = tokens;
	while (temp)
	{
		if (temp->type >= LESS && temp->type <= LESSLESS)
		{
			command->redirections = malloc(sizeof(t_token));
			if (!command->redirections)
				exit(EXIT_FAILURE);
			command->redirections->id = temp->id;
			command->redirections->value = ft_strdup(temp->value);
			command->redirections->type = temp->type;
			command->redirections->prev = NULL;
			command->redirections->next = temp->next;
			command->redirections->next->id = temp->next->id;
			command->redirections->next->value = ft_strdup(temp->next->value);
			command->redirections->next->type = temp->next->type;
			command->redirections->next->prev = command->redirections;
			command->redirections->next->next = NULL;
			// remove_redir_from_tokens(&tokens, temp->id);
			// remove_redir_from_tokens(&tokens, temp->next->id);
		}
		temp = temp->next;
	}
	// current = command->redirections;
	// while (current)
	// {
	// 	printf("Current value: %s\n", current->value);
	// 	if (current->prev)
	// 	{
	// 		printf("Prev value: %s\n", current->prev->value);
	// 	}
	// 	else
	// 	{
	// 		printf("Prev is NULL\n");
	// 	}
	// 	if (current->next)
	// 	{
	// 		printf("Next value: %s\n", current->next->value);
	// 	}
	// 	else
	// 	{
	// 		printf("Next is NULL\n");
	// 	}
	// 	current = current->next;	
	// }
	// while (tokens)
	// {
	// 	printf("tokens: %s\n", tokens->value);
	// 	tokens = tokens->next;
	// }
}
// function that creates a new command struct and adds redirections (if exists) and command arr to it

t_command	*get_new_command(t_token *tokens)
{
	t_token		*temp;
	t_command	*command;
	command = init_command();
	temp = tokens;
	handle_redirections(tokens, command);
	command->cmd_name = get_cmd_from_tokens(tokens);
	return (command);
}

int	parser(t_token *tokens)
{
	t_command	**commands;
	t_token		*temp;
    
    temp = tokens;
    commands = (t_command **)malloc(sizeof(t_command));
	*commands = NULL;
	while (temp)
	{
		if (temp->type == PIPE)
		{
			// get_new_command(tokens);
			add_command_back(commands, get_new_command(tokens));
			// remove_cmd_from_tokens(&tokens);
		}
		temp = temp->next;
	}
	while (*commands)
	{
		printf("Command: %s\n", (*commands)->cmd_name[0]);
		printf("Command: %s\n", (*commands)->cmd_name[1]);
		printf("Command: %s\n", (*commands)->cmd_name[2]);
		printf("Command: %s\n", (*commands)->cmd_name[3]);
		printf("Redir val: %s\n", (*commands)->redirections->value);
		printf("Redir type: %d\n", (*commands)->redirections->type);
		printf("Redir next val: %s\n", (*commands)->redirections->next->value);
		printf("Redir next type: %d\n", (*commands)->redirections->next->type);
		*commands = (*commands)->next;
	}	
	return (0);
}
