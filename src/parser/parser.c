/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:27:28 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/02 15:03:34 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_string_len(t_token *tokens)
{
	int		len;
	t_token	*temp;

	len = 0;
	temp = tokens;
	while (temp && temp->type != PIPE && temp->value)
	{
		len += ft_strlen(temp->value);
		temp = temp->next;
	}
	return (len);
}

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

// function that returns an array of strings (command) from the tokens list
int	process_tokens(t_token *tokens, char **array, int i)
{
	t_token	*temp;

	temp = tokens;
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
	return (i);
}
t_token	*get_cmd_from_tokens(t_token *tokens, t_command *command)
{
	int		num_tokens;
	int		i;
	char	**array;

	i = 0;
	array = NULL;
	num_tokens = count_cmd_before_pipe(tokens);
	array = malloc((num_tokens + 1) * sizeof(char *));
	if (!array)
		exit(EXIT_FAILURE);
	i = process_tokens(tokens, array, i);
	array[i] = NULL;
	if (array[0] == NULL)
	{
		free_array(array);
		command->cmd_name = NULL;
	}
	else
		command->cmd_name = array;
	return (tokens);
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

t_command	*get_command(t_token *tokens, t_command *commands, t_shell *shell)
{
	t_command	*command;

	command = init_command();
	expander(tokens, shell);
	tokens = get_cmd_from_tokens(tokens, command);
	if (tokens)
		handle_redirections(tokens, command, &commands);
	if (command->cmd_name == NULL && command->redirections == NULL)
	{
		free(command);
		return (NULL);
	}
	if (command->cmd_name)
		command->is_builtin = is_builtin(command->cmd_name[0]);
	return (command);
}

int	parser(t_shell *shell)
{
	t_token	*temp;

	temp = shell->tokens;
	while (temp)
	{
		if (no_pipe_in_list(temp) == 1)
		{
			add_command_back(&shell->commands, get_command(shell->tokens,
					shell->commands, shell));
			break ;
		}
		add_command_back(&shell->commands, get_command(shell->tokens,
				shell->commands, shell));
		shell->tokens = remove_pipes(shell->tokens,
				count_tokens_before_pipe(shell->tokens));
		temp = shell->tokens;
		if (temp)
			temp = temp->next;
	}
	//print_commands(shell->commands);
	return (EXIT_SUCCESS);
}
