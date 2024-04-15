/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:27:28 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/15 12:14:59 by jlabonde         ###   ########.fr       */
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
	if (temp->type == PIPE)
		temp = temp->next;
	while (temp && temp->type != PIPE)
	{
		count++;
		temp = temp->next;
	}
	return (count);
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
	if (no_pipe_in_list(tokens))
	{
		if (tokens && tokens->id == id)
		{
			temp = tokens;
			tokens = tokens->next;
			free(temp);
		}
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
	if (temp->type == PIPE)
		temp = temp->next;
	while (i < num_tokens && temp)
	{
		array[i] = temp->value ? ft_strdup(temp->value) : NULL;
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
	t_token *next;

	if (!tokens)
		return ;
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
			next = temp->next ? temp->next->next : NULL;
			if (temp->next)
			{
				add_token_back(redirections, create_token(temp->next->value, temp->next->type));
				tokens = remove_token_by_id(tokens, temp->next->id);
			}
			tokens = remove_token_by_id(tokens, temp->id);
			temp = next;
			break ;
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
		if (temp->type == PIPE)
		{
			add_command_back(commands, get_new_command(tokens));
			tokens = remove_cmd_from_tokens(tokens, temp->id);
			temp = tokens;
		}
		else if (no_pipe_in_list(temp))
		{
			add_command_back(commands, get_new_command(tokens));
			free_stack(&tokens);
			break ;
		}
		if (temp)
			temp = temp->next;
	}
	print_commands(*commands);
	return (0);
}
