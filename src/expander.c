/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/19 14:26:28 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expander(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		temp->value = get_value_after_expansion(temp->value);
		temp = temp->next;
	}
	return (0);
}

/* function that returns the value of the buffer */

char	*get_value_after_expansion(char *token)
{
	char	*new_token;
	char	*buffer;

	buffer = get_buffer_value(token);
	new_token = get_value_from_buffer(buffer);
	if (!new_token)
		return (NULL);
	free(buffer);
	return (new_token);
}

/* function that checks if a string needs to be expanded depending of
what's before and after dollar sign */

int	expansion_needed(char *str, int quotes)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0' && str[i
				+ 1] != '$' && str[i + 1] != S_QUOTE && str[i + 1] != D_QUOTE)
			&& quotes)
			return (1);
		i++;
	}
	return (0);
}

/* function that returns 1 if a string is subject to expansion depending
on its position in relation to single and double quotes */

int	quotes_check(char *str)
{
	int	i;
	int	in_double_quotes;
	int	in_single_quotes;
	int	has_quotes;

	i = 0;
	in_double_quotes = 0;
	in_single_quotes = 0;
	has_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			has_quotes = 1;
		}
		else if (str[i] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			has_quotes = 1;
		}
		else if (str[i] == '$')
		{
			if (in_double_quotes || (in_single_quotes && in_double_quotes))
				return (1);
			else if (in_single_quotes && !in_double_quotes)
				return (0);
		}
		i++;
	}
	return (!has_quotes);
}

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
