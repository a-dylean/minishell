/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/23 17:49:51 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expander(t_token *tokens, t_shell *shell)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		temp->value = get_value_after_expansion(temp->value, shell);
		temp = temp->next;
	}
	return (0);
}

/* function that returns the value of the buffer */

char	*get_value_after_expansion(char *token, t_shell *shell)
{
	char	*new_token;
	char	*buffer;

	buffer = get_buffer_value(token, shell);
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

// int	quotes_check(char *str)
// {
// 	int	i;
// 	int	in_double_quotes;
// 	int	in_single_quotes;
// 	int	has_quotes;

// 	i = 0;
// 	in_double_quotes = 0;
// 	in_single_quotes = 0;
// 	has_quotes = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\"' && !in_single_quotes)
// 		{
// 			in_double_quotes = !in_double_quotes;
// 			has_quotes = 1;
// 		}
// 		else if (str[i] == '\'' && !in_double_quotes)
// 		{
// 			in_single_quotes = !in_single_quotes;
// 			has_quotes = 1;
// 		}
// 		else if (str[i] == '$')
// 		{
// 			if (in_double_quotes || (in_single_quotes && in_double_quotes))
// 				return (1);
// 			else if (in_single_quotes && !in_double_quotes)
// 				return (0);
// 		}
// 		i++;
// 	}
// 	return (!has_quotes);
// }

int quotes_check(char *str) {
    int inside_single_quotes = 0;
    int inside_double_quotes = 0;

    while (*str) {
        if (*str == '\'') {
            inside_single_quotes = !inside_single_quotes;
        } else if (*str == '"') {
            inside_double_quotes = !inside_double_quotes;
        } else if (*str == '$') {
            if (!inside_single_quotes)
                return 1;
		}
        str++;
    }
    return 0;
}

// int	check_double_quotes(char *str, int *i, int *in_single_quotes, int *in_double_quotes, int *has_quotes)
// {
//     if (str[*i] == '\"' && !(*in_single_quotes))
//     {
//         *in_double_quotes = !(*in_double_quotes);
//         *has_quotes = 1;
//     }
//     return (*has_quotes);
// }

// int	check_single_quotes(char *str, int *i, int *in_single_quotes, int *in_double_quotes, int *has_quotes)
// {
//     if (str[*i] == '\'' && !(*in_double_quotes))
//     {
//         *in_single_quotes = !(*in_single_quotes);
//         *has_quotes = 1;
//     }
//     return (*has_quotes);
// }

// int	check_dollar_sign(char *str, int *i, int *in_single_quotes, int *in_double_quotes)
// {
//     if (str[*i] == '$')
//     {
//         if (*in_double_quotes || (*in_single_quotes && *in_double_quotes))
//             return (1);
//         else if (*in_single_quotes && !(*in_double_quotes))
//             return (0);
//     }
//     return (-1);
// }

// int	quotes_check(char *str)
// {
//     int	i;
//     int	in_double_quotes;
//     int	in_single_quotes;
//     int	has_quotes;
//     int	dollar_check;

//     i = 0;
//     in_double_quotes = 0;
//     in_single_quotes = 0;
//     has_quotes = 0;
//     while (str[i])
//     {
//         has_quotes = check_double_quotes(str, &i, &in_single_quotes, &in_double_quotes, &has_quotes);
//         has_quotes = check_single_quotes(str, &i, &in_single_quotes, &in_double_quotes, &has_quotes);
//         dollar_check = check_dollar_sign(str, &i, &in_single_quotes, &in_double_quotes);
//         if (dollar_check != -1)
//             return (dollar_check);
//         i++;
//     }
//     return (!has_quotes);
// }

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
