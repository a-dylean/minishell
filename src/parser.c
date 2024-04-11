/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:27:28 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/11 19:24:44 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_tokens_before_pipe(t_token *tokens)
{
    int count = 0;
    t_token *temp;
    
    temp = tokens;
    while (temp && temp->type != PIPE)
    {
        count++;
        temp = temp->next;
    }
    return (count);
}

void remove_redir_from_tokens(t_token *tokens)
{
    while (tokens)
    {
        if (tokens->type >= LESS && tokens->type <= LESSLESS)
        {
            tokens = tokens->next->next;
            free(tokens);
            free(tokens->next);
            break;
        }
        tokens = tokens->next;
    }
}

void remove_cmd_from_tokens(t_token **tokens)
{
    t_token *temp;
    
    int num_of_nodes = count_tokens_before_pipe(*tokens);
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
    int num_tokens;
    int i;
    t_token *temp;
    char **array;

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
    t_token *temp;
    
    temp = tokens;
    command->redirections = temp;
    command->redirections->next = temp->next;
    command->redirections->next->next = NULL;
    remove_redir_from_tokens(tokens);
}
// function that creates a new command struct and adds redirections (if exists) and command arr to it
t_command   *get_new_command(t_token *tokens)
{
    t_token *temp;
    t_command *command;
    
    temp = tokens;
    command = init_command();
    while (temp)
	{
        if (temp->type >= LESS && temp->type <= LESSLESS)
            handle_redirections(tokens, command);
		temp = temp->next;
	}
    command->cmd_name = get_cmd_from_tokens(tokens);
    return (command);
}

int	parser(t_token *tokens)
{
	t_command	**commands;
    t_token *temp;
    
    temp = tokens;
    commands = (t_command **)malloc(sizeof(t_command));
	*commands = NULL;
	while (temp)
	{
		if (temp->type == PIPE)
		{
            add_command_back(commands, get_new_command(tokens));
            remove_cmd_from_tokens(&tokens);
		}
		temp = temp->next;
	}
    t_command *current_command = *commands;
    while (current_command)
    {
        printf("cmd_name: %s\n", current_command->cmd_name[0]);
        current_command = current_command->next;
    }
	return (0);
}
