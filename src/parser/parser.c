/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:27:28 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/30 15:20:48 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_cmd_array_from_tokens(t_token *tokens)
{
	char	**cmd_array;
	int		i;

	i = -1;
	cmd_array = malloc((count_not_null_tokens(tokens) + 1) * sizeof(char *));
	if (cmd_array == NULL)
		return (NULL);
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->value && tokens->value[0] != '\0' && tokens->type == WORD)
		{
			cmd_array[++i] = ft_strdup(tokens->value);
			if (cmd_array[i] == NULL)
				return (free_array(cmd_array), NULL);
		}
		else if (tokens->value && tokens->type == WORD)
		{
			cmd_array[++i] = ft_strdup("");
			if (cmd_array[i] == NULL)
				return (free_array(cmd_array), NULL);
		}
		tokens = tokens->next;
	}
	cmd_array[++i] = NULL;
	return (cmd_array);
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
			new_command = get_command(temp);
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
