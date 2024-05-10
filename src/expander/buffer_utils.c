/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:09:01 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/10 13:37:30 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*init_buffer(char *token, t_shell *shell)
{
	char	*buffer;
	int		buffer_size;

	if (token)
		buffer_size = calculate_buffer_size(token, shell);
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
	char	*tmp;

	exit_status = ft_itoa(0);
	if (shell->exit_status)
	{
		free(exit_status);
		exit_status = ft_itoa(shell->exit_status);
	}
	tmp = exit_status;
	while (*exit_status)
	{
		buffer[(*j)++] = *exit_status;
		exit_status++;
	}
	free(tmp);
	token++;
}

/* function that copies the env value to the buffer if it exists
and if it doesn't it doesn't copy anything ($$ is not handeled the bash
way (returning PID) because it's not in the subject) */

void	handle_expansion(char *token, int (*indexes)[2], char *buffer,
		t_shell *shell)
{
	char	*env_var;
	char	*env_var_value;
	char	*tmp;

	env_var = get_env_from_str(&token[*indexes[0]]);
	if (var_exists(shell->env_head, env_var))
	{
		env_var_value = ft_getenv(shell->env_head, env_var);
		tmp = env_var_value;
		while (*env_var_value)
		{
			buffer[(*indexes)[1]++] = *env_var_value;
			env_var_value++;
		}
		free(tmp);
	}
	if (env_var)
		(*indexes)[0] += ft_strlen(env_var) + 1;
	else if (token[(*indexes)[0]] == '$')
		(*indexes[0])++;
	free(env_var);
}

/* function that returns buffer that is the new value for token */

char	*get_buffer_value(char *token, char *buffer, t_shell *shell)
{
	int	indexes[2];

	indexes[0] = 0;
	indexes[1] = 0;
	while (token[indexes[0]])
	{
		if (token[indexes[0]] != '$')
			buffer[indexes[1]++] = token[indexes[0]++];
		else
		{
			if (token[indexes[0] + 1] == '?')
			{
				expand_to_exit_status(&token[indexes[0]], buffer, &indexes[1],
					shell);
				if (token[indexes[0] + 2] == '\0')
					break ;
				indexes[0] += 2;
			}
			else
				handle_expansion(token, &indexes, buffer, shell);
		}
	}
	buffer[indexes[1]] = '\0';
	return (buffer);
}
