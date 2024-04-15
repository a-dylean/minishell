/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/15 16:26:08 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expander(t_command *commands)
{
	t_command	*temp;
	t_token		*temp_token;

	// expand commands
	temp = commands;
	while (temp)
	{
		expand_command(temp);
		temp = temp->next;
	}
	// expand redirections
	temp_token = commands->redirections;
	while (temp_token)
	{
		expand_redirection(temp_token);
		temp_token = temp_token->next;
	}
	return (0);
}

int	has_dollar(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
		return (1);
	i++;
	return (0);
}

void	expand_command(t_command *command)
{
	int i;
	char *env_var;

	i = 0;
	while (command->cmd_name[i])
	{
		if (has_dollar(command->cmd_name[i]))
		{
			env_var = ft_strtrim(command->cmd_name[i], "$");
			if (env_var)
			{
				free(command->cmd_name[i]);
				command->cmd_name[i] = ft_strdup(getenv(env_var));
			}	
			else
				command->cmd_name[i] = NULL;
		}
		i++;
	}
}
void expand_redirection(t_token *redirection)
{
	char *env_var;

	if (has_dollar(redirection->value))
	{
		env_var = ft_strtrim(redirection->value, "$");
		if (env_var)
		{
			free(redirection->value);
			redirection->value = ft_strdup(getenv(env_var));
		}
		else
			redirection->value = NULL;
	}
}