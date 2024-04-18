/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/18 16:41:38 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expander(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp != NULL)
	{
		printf("initial token = %s\n", temp->value);
		temp->value = perform_expansion(temp->value);
		temp = temp->next;
	}
	return (0);
}

/* function that checks if there's a dollar sign in the string
and if other conditions are met for expansion (needs to
to be updated to include more cases with quotes (')) */

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
/* function that extracts value of env from string */

char	*get_env_from_str(char *str)
{
	int		i;
	char	*env_var;

	i = 1;
	while (str[i] && str[i] != '$' && ((ft_isalnum(str[i]) || str[i] == '_')))
		i++;
	env_var = ft_substr(str, 1, i - 1);
	if (env_var)
		return (env_var);
	return (NULL);
}

/* function that checks if env var exists in env list */

int	env_var_exists(char *env_var)
{
	char	*env_var_value;

	if (env_var == NULL)
		return (0);
	env_var_value = getenv(env_var);
	if (env_var_value)
		return (1);
	return (0);
}

/* function that checks quotes */

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

/* function that returns new value for token if expansion is needed */

char	*perform_expansion(char *token)
{
	char	buffer[256] = {0};
	int		i;
	int		j;
	int		quotes;
	char	*env_var;
	char	*env_var_value;
	char	*new_token;

	i = 0;
	j = 0;
	quotes = quotes_check(token);
	while (token[i])
	{
		if (token[i] != '$')
		{
			buffer[j] = token[i];
			i++;
			j++;
		}
		else
		{
			if (expansion_needed(&token[i], quotes))
			{
				env_var = get_env_from_str(&token[i]);
				if (env_var_exists(env_var))
				{
					env_var_value = getenv(env_var);
					while (*env_var_value)
					{
						buffer[j] = *env_var_value;
						env_var_value++;
						j++;
					}
				}
				i += ft_strlen(env_var) + 1;
			}
			else
			{
				buffer[j] = token[i];
				i++;
				j++;
			}
		}
	}
	buffer[j] = '\0';
	new_token = ft_strdup(buffer);
	if (!new_token)
		return (NULL);
	free(token);
	return (new_token);
}
