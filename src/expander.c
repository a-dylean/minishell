/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/16 19:29:36 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expander(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp != NULL)
	{
		if (has_dollar(temp->value))
			temp->value = perform_expansion(temp->value);
		temp = temp->next;
	}
	return (0);
}

int	has_dollar(char *str)
{
    int	i;

    i = 0;
    if (str == NULL)
        return (0);
    while (str[i])
    {
        if ((str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0')
            || (i > 0 && str[i] == '$' && str[i - 1] == ' ') 
            || (i > 0 && str[i] == '$' && str[i - 1] == '"'))
            return (1);
        i++;
    }
    return (0);
}

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

int	str_is_empty_or_space_only(const char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*join_strings_with_spaces(char **strings)
{
	char	*joined_string;
	int		i;
	char	*temp;
	
	joined_string = NULL;
	i = 0;
	while (strings[i] && str_is_empty_or_space_only(strings[i]))
		i++;
	if (strings[i] == NULL)
		joined_string = ft_strdup(" ");
	else
		joined_string = ft_strdup(strings[i]);
	i++;
	while (strings[i])
	{
		if (!str_is_empty_or_space_only(strings[i]))
		{
			temp = ft_strjoin(joined_string, " ");
			free(joined_string);
			joined_string = ft_strjoin(temp, strings[i]);
			free(temp);
		}
		i++;
	}
	return (joined_string);
}

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
		if (has_dollar(split_token[i]))
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
