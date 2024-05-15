/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:27:28 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/15 13:41:57 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_not_null_tokens(t_token *tokens)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = tokens;
	if (temp->type == PIPE)
		temp = temp->next;
	while (temp && temp->type != PIPE)
	{
		if (temp->value)
			count++;
		temp = temp->next;
	}
	return (count);
}
char	**get_cmd_array_from_tokens(t_token *tokens)
{
	char	**array;
	int		i;

	i = 0;
	array = malloc(sizeof(char *) * (count_not_null_tokens(tokens) + 1));
	if (!array)
		return (NULL);
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
		{
			if (tokens->value != NULL && tokens->value[0] != '\0')
			{
				array[i] = ft_strdup(tokens->value);
				if (!array[i])
					return (free_array(array), NULL);
				i++;
			}
			else if (tokens->value != NULL)
			{
				array[i] = ft_strdup("");
				if (!array[i])
					return (free_array(array), NULL);
				i++;
			}
		}
		tokens = tokens->next;
	}
	array[i] = NULL;
	return (array);
}

bool	is_builtin(char *cmd)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strcmp("echo", cmd) || !ft_strcmp("cd", cmd)
			|| !ft_strcmp("pwd", cmd) || !ft_strcmp("export", cmd)
			|| !ft_strcmp("unset", cmd) || !ft_strcmp("env", cmd)
			|| !ft_strcmp("exit", cmd))
			return (true);
		i++;
	}
	return (false);
}

t_command	*get_command(t_token *tokens, t_shell *shell)
{
	t_command	*command;

	if (!tokens)
		return (NULL);
	expander(tokens, shell);
	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	ft_memset(command, 0, sizeof(t_command));
	command->cmd_name = get_cmd_array_from_tokens(tokens);
	handle_redirections(tokens, command);
	if (command->cmd_name && command->cmd_name[0])
		command->is_builtin = is_builtin(command->cmd_name[0]);
	return (command);
}

t_token	*get_next_pipe(t_token *token)
{
	if (!token)
		return (NULL);
	while (token)
	{
		if (token->type == PIPE)
			return (token);
		token = token->next;
	}
	return (NULL);
}

int	parser(t_shell *shell)
{
	t_token		*temp;
	t_command	*new_command;

	temp = shell->tokens;
	shell->commands = NULL;
	while (temp)
	{
		if (temp->type != PIPE)
		{
			new_command = get_command(temp, shell);
			if (!new_command)
				return (free_commands(&shell->commands), -1);
			add_command_back(&shell->commands, new_command);
			temp = get_next_pipe(temp);
			if (!temp)
				break ;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
