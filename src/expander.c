/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/16 19:47:02 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expander(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp != NULL)
	{
		if (expansion_needed(temp->value))
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
	int		j;
	char	*env_var;
	char	*temp;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	j = i + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	temp = ft_substr(str, i + 1, j - i - 1);
	if (!temp)
		return (NULL);
	env_var = ft_strtrim(temp, "$\"");
	if (env_var)
		return (env_var);
	free(temp);
	return (NULL);
}
/* function that split token string by spaces, checks if a token in string 
is subject to expansion, if so, replaces it with env var and then joins tokens back */

char	*perform_expansion(char *token)
{
	char	**split_token;
	char	*expanded_token;
	char	*env_var;
	char	*env_value;
	int		i;

	i = -1;
	split_token = ft_split(token, ' ');
	while (split_token[++i])
	{
		if (expansion_needed(split_token[i]))
		{
			env_var = get_env_from_str(split_token[i]);
			env_value = getenv(env_var);
			free(split_token[i]);
			split_token[i] = ft_strdup(" ");
			if (env_value)
				split_token[i] = ft_strdup(env_value);
			free(env_var);
		}
	}
	expanded_token = join_strings_with_spaces(split_token);
	free_array(split_token);
	free(token);
	token = ft_strdup(expanded_token);
	free(expanded_token);
	return (token);
}
