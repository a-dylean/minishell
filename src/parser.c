/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:27:28 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/18 14:34:04 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*remove_cmd_from_tokens(t_token *tokens, int id)
{
	t_token	*temp;
	int	i = 0;

	while (tokens && i != id)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp);
		i++;
	}
	if (tokens && no_pipe_in_list(tokens))
	{
		if (i == id)
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

int	count_cmd_before_pipe(t_token *tokens)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = tokens;
	if (temp->type == PIPE)
		temp = temp->next;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == WORD)
			count++;
		temp = temp->next;
	}
	return (count);
}

t_token	*ft_lexerclear_one(t_token **tokens)
{
	if ((*tokens)->value)
	{
		free((*tokens)->value);
		(*tokens)->value = NULL;
	}
	// free(*tokens);
	// *tokens = NULL;
	return (NULL);
}

void	ft_lexerdel_first(t_token **tokens)
{
	t_token	*node;

	node = *tokens;
	*tokens = node->next;
	ft_lexerclear_one(&node);
	if (*tokens)
		(*tokens)->prev = NULL;
}

void	delete_next_word(t_token **tokens)
{
	t_token	*node;
	t_token	*prev;
	t_token	*start;

	start = *tokens;
	node = start;
	
	if ((*tokens)->type == WORD)
	{
		ft_lexerdel_first(tokens);
		return ;
	}
	while (node && node->type != WORD)
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

char **get_cmd_among_redirection(t_token *tokens)
{
	int	num_tokens;
	int	i;
	t_token	*temp;
	char	**array;

	i = 0;
	temp = tokens;
	array = NULL;
	num_tokens = count_cmd_before_pipe(tokens);
	array = malloc((num_tokens + 1) * sizeof(char *));
	if (!array)
		exit(EXIT_FAILURE);
	if (temp && temp->type == PIPE)
		temp = temp->next;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == WORD)
		{
			if (temp->value != NULL)
			{
				array[i] = ft_strdup(temp->value);
				delete_next_word(&tokens);
				i++;
			}
		}
		temp = temp->next;
	}
	array[i] = NULL;
	return (array);
}

t_command *redirection_start(t_token *tokens)
{
	t_command	*command;

	command = init_command();
	command->cmd_name = get_cmd_among_redirection(tokens);
	handle_redirections(tokens, command);
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

void	assign_type_redirections(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == GREAT && (tokens->next && tokens->next->type == WORD))
			tokens->next->type = FILENAME;
		else if (tokens->type == LESS && (tokens->next && tokens->next->type == WORD))
			tokens->next->type = FILENAME;
		else if (tokens->type == LESSLESS && (tokens->next && tokens->next->type == WORD))
			tokens->next->type = DELIMITER;
		else if (tokens->type == GREATGREAT && (tokens->next && tokens->next->type == WORD))
			tokens->next->type = FILENAME;
		tokens = tokens->next;
	}
}

int	parser(t_token *tokens)
{
	t_command	**commands;
	t_token		*temp;

	temp = tokens;
	commands = (t_command **)malloc(sizeof(t_command));
	*commands = NULL;
	assign_type_redirections(tokens);
	while (temp)
	{
		if (temp->type == PIPE || (no_pipe_in_list(temp) == 1 && temp->type == WORD))
		{
			add_command_back(commands, get_new_command(tokens));
			tokens = remove_cmd_from_tokens(tokens, count_tokens_before_pipe(tokens));
			temp = tokens;
		}
		else if (no_pipe_in_list(temp) == 1)
		{
			add_command_back(commands, redirection_start(tokens));
			break ;
		}
		if (temp)
			temp = temp->next;

	}
	print_commands(*commands);
	return (0);
}
