/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:27:28 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/17 12:25:47 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*remove_cmd_from_tokens(t_token *tokens, int id)
{
	t_token	*temp;

	while (tokens && tokens->id != id)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp);
	}
	if (tokens && no_pipe_in_list(tokens))
	{
		if (tokens->id == id)
		{
			temp = tokens;
			tokens = tokens->next;
			free(temp);
		}
	}
	if (tokens == NULL)
		return (NULL);
	return (tokens);
}

// t_token *remove_cmd_from_tokens(t_token *tokens, int id)
// {
//     t_token *temp = tokens;
//     t_token *prev = NULL;
//     t_token *head = tokens;

//     while (temp && temp->id != id)
//     {
//         prev = temp;
//         temp = temp->next;
//     }

//     if (temp && no_pipe_in_list(tokens))
//     {
//         if (temp->id == id)
//         {
//             if (prev)
//             {
//                 prev->next = temp->next;
//             }
//             else
//             {
//                 head = temp->next;
//             }
//             free(temp);
//         }
//     }
// 	printf("remove_cmd_from_tokens\n");
//     return head;
// }

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
	if (temp && temp->type == PIPE)
		temp = temp->next;
	while (i < num_tokens && temp)
	{
		if (temp->value != NULL)
			array[i] = ft_strdup(temp->value);
		else
			array[i] = NULL;
		temp = temp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

// function that creates a new command struct and adds redirections (if exists) 
// and command arr to it
t_command	*get_new_command(t_token *tokens)
{
	t_command	*command;

	command = init_command();
	handle_redirections(tokens, command);
	command->cmd_name = get_cmd_from_tokens(tokens);
	return (command);
}

int	len_stack(t_token *stack)
{
	t_token	*current;
	int		i;

	current = stack;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
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
			if (temp->type == WORD)
			{
				add_command_back(commands, get_new_command(tokens));
				tokens = remove_cmd_from_tokens(tokens, temp->id);
				temp = tokens;
			}
			else
				add_command_back(commands, get_new_command(tokens));
		}
		if (temp)
			temp = temp->next;
	}
	print_commands(*commands);
	return (0);
}
