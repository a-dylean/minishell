/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:09:01 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/26 14:04:07 by atonkopi         ###   ########.fr       */
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

/* function that copies the buffer to a new token */

char	*get_value_from_buffer(char buffer[])
{
	char	*new_token;

	new_token = ft_strdup(buffer);
	if (!new_token)
		return (NULL);
	return (new_token);
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
/* function that copies the env value to the buffer if it exists
and if it doesn't it doesn't copy anything ($$ is not handeled the bash
way (returning PID) because it's not in the subject) */

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
	if (env_var)
		*i += ft_strlen(env_var) + 1;
	else if (token[*i] == '$')
		(*i)++;
	free(env_var);
}

/* function that returns buffer that is the new value for token */

char	*get_buffer_value(char *token, char *buffer, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
					break ;
				i += 2;
			}
			else
				handle_expansion(token, &i, buffer, &j);
		}
	}
	buffer[j] = '\0';
	return (buffer);
}
