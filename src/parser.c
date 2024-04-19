/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:27:28 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/19 14:37:33 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*remove_pipes(t_token *tokens, int id)
{
	t_token	*temp;
	int		i;

	i = 0;
	if (id == 0 && tokens->type == PIPE)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp);
		return (tokens);
	}
	while (tokens && i != id)
	{
		if (tokens->type != PIPE)
		{
			temp = tokens;
			tokens = tokens->next;
			free(temp);
			i++;
		}
		else
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

t_token	*get_cmd_among_redirection(t_token *tokens, t_command *command)
{
	int		num_tokens;
	int		i;
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
				delete_next_type(&tokens, WORD);
				i++;
			}
		}
		temp = temp->next;
	}
	array[i] = NULL;
	if (array[0] == NULL)
	{
		free(array);
		command->cmd_name = NULL;
		return (tokens);
	}
	else
		command->cmd_name = array;
	return (tokens);
}

t_command *get_command(t_token *tokens)
{
	t_command	*command;

	command = init_command();
	tokens = get_cmd_among_redirection(tokens, command);
	if (tokens)
		handle_redirections(tokens, command);
	if (command->cmd_name == NULL && command->redirections == NULL)
	{
		free(command);
		return (NULL);
	}
	return (command);
}

void	assign_type_redirections(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == GREAT && (tokens->next
				&& tokens->next->type == WORD))
			tokens->next->type = FILENAME;
		else if (tokens->type == LESS && (tokens->next
				&& tokens->next->type == WORD))
			tokens->next->type = FILENAME;
		else if (tokens->type == LESSLESS && (tokens->next
				&& tokens->next->type == WORD))
			tokens->next->type = DELIMITER;
		else if (tokens->type == GREATGREAT && (tokens->next
				&& tokens->next->type == WORD))
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
	if (!commands)
		exit(EXIT_FAILURE);
	*commands = NULL;
	assign_type_redirections(tokens);
	while (temp)
	{
		if (no_pipe_in_list(temp) == 1)
		{
			add_command_back(commands, get_command(tokens));
			break ;
		}
		add_command_back(commands, get_command(tokens));
		tokens = remove_pipes(tokens, count_tokens_before_pipe(tokens));
		temp = tokens;
		if (temp)
			temp = temp->next;
	}
	print_commands(*commands);
	return (0);
}
