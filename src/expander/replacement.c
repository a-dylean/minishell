/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:25:51 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/24 16:14:16 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* function that calculates the size of the expansion
that will be added to the buffer */

int	calculate_expansion_size(char *token, int *i)
{
	int		buffer_size;
	char	*env_var_value;
	char	*env_var;

	buffer_size = 0;
	env_var = get_env_from_str(&token[*i]);
	if (env_var_exists(env_var))
	{
		env_var_value = getenv(env_var);
		if (env_var_value)
			buffer_size += ft_strlen(env_var_value);
	}
	if (env_var)
		*i += ft_strlen(env_var) + 1;
	else
		*i += 1;
	return (buffer_size);
}

/* function that returns the value of the buffer */

char	*get_value_after_expansion(char *token, t_shell *shell)
{
	char	*new_token;
	char	*buffer;

	buffer = init_buffer(token);
	if (!buffer)
		return (NULL);
	buffer = get_buffer_value(token, buffer, shell);
	new_token = get_value_from_buffer(buffer);
	if (!new_token)
		return (NULL);
	free(buffer);
	return (new_token);
}

int replace_with_expansion(t_token **token, t_shell *shell)
{
	(void)shell;
	
	printf("Str for expansion: %s\n", (*token)->value);
	(*token)->value = get_value_after_expansion((*token)->value, shell);
	return (0);
}