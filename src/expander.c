/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/17 16:35:29 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expander(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp != NULL)
	{
		temp->value = perform_expansion(temp->value);
		temp = temp->next;
	}
	return (0);
}

/* function that checks if there's a dollar sign in the string
and if other conditions are met for expansion (needs to
to be updated to include more cases with quotes (')) */

int	expansion_needed(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0') || (i > 0
				&& str[i] == '$' && str[i - 1] == ' ') || (i > 0
				&& str[i] == '$' && str[i - 1] == '"'))
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

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	env_var = ft_substr(str, 0, i);
	return (env_var);
}

/* function that split token string by spaces, checks if a token in string
is subject to expansion, if so,
	replaces it with env var and then joins tokens back */

// char	*perform_expansion(char *token)
// {
// 	char	**split_token;
// 	char	*expanded_token;
// 	char	*env_var;
// 	char	*env_value;
// 	int		i;
// 	int		j;
// 	char	**split_by_dollar;

// 	i = -1;
// 	split_token = ft_split(token, ' ');
// 	while (split_token[++i])
// 	{
// 		if (expansion_needed(split_token[i]))
// 		{
// 			split_by_dollar = ft_split(split_token[i], '$');
// 			j = -1;
// 			while (split_by_dollar[++j])
// 			{
// 				env_var = get_env_from_str(split_by_dollar[j]);
// 				if (env_var)
// 					env_value = getenv(env_var);
// 				else
// 					env_value = NULL;
// 				// free(split_by_dollar[j]);
// 				if (env_value)
// 					split_by_dollar[j] = ft_strdup(env_value);
// 				else
// 					split_by_dollar[j] = ft_strdup(" ");
// 				free(env_var);
// 			}
// 			if (count_chars(split_token[i], '$') > 1)
// 				split_token[i] = join_strings(split_by_dollar, "");
// 			else
// 				split_token[i] = join_strings(split_by_dollar, " ");
// 			free_array(split_by_dollar);
// 		}
// 	}
// 	expanded_token = join_strings(split_token, " ");
// 	free_array(split_token);
// 	free(token);
// 	token = ft_strdup(expanded_token);
// 	free(expanded_token);
// 	return (token);
// }

char	**expand_token(char **split_by_dollar)
{
	int		j;
	char	*env_var;
	char	*env_value;

	j = -1;
	while (split_by_dollar[++j])
	{
		env_var = get_env_from_str(split_by_dollar[j]);
		if (env_var)
			env_value = getenv(env_var);
		else
			env_value = NULL;
		if (env_value)
			split_by_dollar[j] = ft_strdup(env_value);
		else
			split_by_dollar[j] = ft_strdup("");
		free(env_var);
	}
	return (split_by_dollar);
}

char	*join_expanded_token(char **split_by_dollar, char *split_token_i)
{
	if (count_chars(split_token_i, '$') > 1)
		return (join_strings(split_by_dollar, ""));
	else
		return (join_strings(split_by_dollar, " "));
}

char	*perform_expansion(char *token)
{
	char **split_token;
	char *expanded_token;
	int i;
	char **split_by_dollar;

	i = -1;
	split_token = ft_split(token, ' ');
	while (split_token[++i])
	{
		if (expansion_needed(split_token[i]))
		{
			split_by_dollar = ft_split(split_token[i], '$');
			split_by_dollar = expand_token(split_by_dollar);
			split_token[i] = join_expanded_token(split_by_dollar,
					split_token[i]);
			free_array(split_by_dollar);
		}
	}
	expanded_token = join_strings(split_token, " ");
	free_array(split_token);
	free(token);
	token = ft_strdup(expanded_token);
	free(expanded_token);
	return (token);
}
