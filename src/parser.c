/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:27:28 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/18 16:26:49 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*remove_cmd_from_tokens(t_token *tokens, int id)
{
	t_token	*temp;
	t_token	*head;

	head = tokens;
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
		return (head);
	return (tokens);
}
int cmd_string_len(t_token *tokens)
{
	int len;
	t_token *temp;

	len = 0;
	temp = tokens;
	while (temp && temp->type != PIPE && temp->value)
	{
		len += ft_strlen(temp->value);
		temp = temp->next;
	}
	return (len);
}
// function that returns an array of strings (command) from the tokens list

char	**get_cmd_from_tokens(t_token *tokens, int num_tokens)
{
    int		i;
    t_token	*temp;
    char	*cmd_str;
    char	**array;

    i = 0;
    temp = tokens;
    cmd_str = malloc(cmd_string_len(tokens) + 1);
    cmd_str[0] = '\0';
    if (temp->type == PIPE)
        temp = temp->next;
    while (i < num_tokens && temp)
    {
        if (temp->value)
        {
            strcat(cmd_str, temp->value);
            if (temp->next)
                strcat(cmd_str, "!");
        }
        temp = temp->next;
        i++;
    }
    array = ft_split(cmd_str, '!');
	free(cmd_str);
    return (array);
}

// function that creates a new command struct and adds redirections (if exists)
// and command arr to it
t_command	*get_new_command(t_token *tokens)
{
	t_command	*command;
	int			num_tokens;

	command = init_command();
	num_tokens = count_tokens_before_pipe(tokens);
	expander(tokens);
	handle_redirections(tokens, command);
	command->cmd_name = get_cmd_from_tokens(tokens, num_tokens);
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
	// remove single & double quotes here ??
	print_commands(*commands);
	return (0);
}
