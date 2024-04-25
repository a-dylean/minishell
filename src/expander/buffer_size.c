/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:25:51 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/25 16:28:04 by atonkopi         ###   ########.fr       */
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
