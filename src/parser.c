/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:27:28 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/12 18:23:29 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *remove_token_by_id(t_token *tokens, int id) {
    t_token *temp;
    if(tokens == NULL) {
        return NULL;
    }

    if(tokens->id == id) {
        temp = tokens->next;
        free(tokens);
        return temp;
    }

    t_token *current = tokens;
    while(current->next != NULL) {
        if(current->next->id == id) {
            temp = current->next->next;
            free(current->next);
            current->next = temp;
            if(temp != NULL) {
                temp->prev = current;
            }
            break;
        }
        current = current->next;
    }
    return tokens;
}

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
t_token	*clear_one_token(t_token **lst)
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

void	delete_first_token(t_token **lst)
{
	t_token	*node;

	node = *lst;
	*lst = node->next;
	clear_one_token(&node);
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
		delete_first_token(tokens);
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
	clear_one_token(&node);
	*tokens = start;
}

t_token *remove_cmd_from_tokens(t_token *tokens, int id)
{
    t_token *temp;
    t_token *head = tokens;
    while (tokens && tokens->id != id)
    {
        temp = tokens;
        tokens = tokens->next;
        free(temp);
    }
    if (tokens == NULL) 
        return head;
    return tokens;
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
	t_token **redirections;

	if (!tokens)
	{
		printf("No tokens\n");
		return ;
	}
	redirections = (t_token **)malloc(sizeof(t_token));
	if (!redirections)
		exit(EXIT_FAILURE);
	*redirections = NULL;
	temp = tokens;
	while (temp)
	{
		if (temp->type >= LESS && temp->type <= LESSLESS)
		{
			add_token_back(redirections, create_token(temp->value, temp->type));
			add_token_back(redirections, create_token(temp->next->value, temp->next->type));
			tokens = remove_token_by_id(tokens, temp->id);
			tokens = remove_token_by_id(tokens, temp->next->id);
		}
		temp = temp->next;
	}
	command->redirections = *redirections;
}
// function that creates a new command struct and adds redirections (if exists) and command arr to it
t_command	*get_new_command(t_token *tokens)
{
	t_command	*command;
	command = init_command();
	handle_redirections(tokens, command);
	t_token *temp = tokens;
	// while(temp)
	// {
	// 	printf("Token: %s\n", temp->value);
	// 	temp = temp->next;
	// }
	command->cmd_name = get_cmd_from_tokens(tokens);
	return (command);
}
int no_pipe_in_list(t_token *tokens)
{
	t_token *temp = tokens;
	while (temp)
	{
		if (temp->type == PIPE)
			return (0);
		temp = temp->next;
	}
	return (1);
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
		if (temp->type == PIPE || no_pipe_in_list(temp))
		{
			add_command_back(commands, get_new_command(tokens));
			tokens = remove_cmd_from_tokens(tokens, temp->id);
			temp = tokens;	
		}
		if (temp)
			temp = temp->next;
	}
	while (*commands)
	{
		printf("Command: %s\n", (*commands)->cmd_name[0]);
		printf("Command: %s\n", (*commands)->cmd_name[1]);
		// printf("Command: %s\n", (*commands)->cmd_name[2]);
		// printf("Command: %s\n", (*commands)->cmd_name[3]);
		printf("Redir val: %s\n", (*commands)->redirections->value);
		printf("Redir type: %d\n", (*commands)->redirections->type);
		printf("Redir next val: %s\n", (*commands)->redirections->next->value);
		printf("Redir next type: %d\n", (*commands)->redirections->next->type);
		*commands = (*commands)->next;
	}	
	return (0);
}
