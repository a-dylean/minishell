/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:09:01 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/23 12:18:57 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* init buffer */

char	*init_buffer(char *token)
{
	char	*buffer;
	int		buffer_size;

	if (token)
		buffer_size = calculate_buffer_size(token);
	else
		return (NULL);
	buffer = malloc(buffer_size + 1);
	if (!buffer)
		return (NULL);
	return (buffer);
}
/* function that returns new value for token if expansion is needed */

char	*get_buffer_value(char *token, t_shell *shell)
{
	char	*buffer;
	int		i;
	int		j;
	int		quotes;

	i = 0;
	j = 0;
	buffer = init_buffer(token);
	if (!buffer)
		return (NULL);
	quotes = quotes_check(token);
	printf("TOKEN[%d]: %c\n", i, token[i]);
	while (token[i])
	{
		if (token[i] != '$')
			buffer[j++] = token[i++];
		else
		{
			if (token[i + 1] == '?')
			{
				expand_to_exit_status(&token[i], buffer, &j, shell);
				if (token[i + 2] == '\0')
					break;
				i += 2;
			}
			if (expansion_needed(&token[i], quotes))
				handle_expansion(token, &i, buffer, &j);
			else
				buffer[j++] = token[i++];
		}
	}
	buffer[j] = '\0';
	return (buffer);
}

void	expand_to_exit_status(char *token, char *buffer, int *j, t_shell *shell)
{
	char	*exit_status;

	exit_status = ft_itoa(shell->exit_status);
	while (*exit_status)
	{
		buffer[(*j)++] = *exit_status;
		exit_status++;
	}
	token++;
}
/* function that copies the env value to the buffer if it exists*/

void	handle_expansion(char *token, int *i, char *buffer, int *j)
{
	char	*env_var;
	char	*env_var_value;

	env_var = get_env_from_str(&token[*i]);
	if (env_var_exists(env_var))
	{
		env_var_value = getenv(env_var);
		while (*env_var_value)
		{
			buffer[(*j)++] = *env_var_value;
			env_var_value++;
		}
	}
	*i += ft_strlen(env_var) + 1;
}

/* function that copies the buffer to a new token */

char	*get_value_from_buffer(char buffer[])
{
	char	*new_token;

	new_token = ft_strdup(buffer);
	if (!new_token)
		return (NULL);
	return (new_token);
}

/* function that calculates the size of the buffer needed for the new token */

int	calculate_buffer_size(char *token)
{
	int	i;
	int	buffer_size;

	i = 0;
	buffer_size = 0;
	while (token[i])
	{
		if (token[i] != '$')
		{
			buffer_size++;
			i++;
		}
		else
			buffer_size += calculate_expansion_size(token, &i);
	}
	return (buffer_size + 1);
}
