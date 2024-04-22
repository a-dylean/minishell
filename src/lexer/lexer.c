/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:58:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/22 13:08:19 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_quotes(char *str)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;
	int	result;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == S_QUOTE)
			in_single_quote = !in_single_quote;
		else if (str[i] == D_QUOTE)
			in_double_quote = !in_double_quote;
		i++;
	}
	result = !(in_single_quote || in_double_quote);
	return (result);
}

int	len_between_quotes(char *str, int i, char quote)
{
	int	len;

	len = 1;
	while (str[i + len] != quote)
		len++;
	len++;
	return (len);
}

int	len_word(char *str, int i)
{
	int	len;

	len = 1;
	while (!ft_isspace(str[i + len]) && str[i + len])
	{
		if (str[i + len] != S_QUOTE && str[i + len] != D_QUOTE
			&& !ft_strchr("|><", str[i + len]))
			len++;
		else
			return (len);
	}
	return (len);
}

int	count_spaces(char *str, int i)
{
	int	len;

	len = 0;
	while (ft_isspace(str[i + len]) && str[i])
		len++;
	return (len);
}

int	*encode_tokens(char *str, t_token **tokens)
{
	int		i;
	int		j;
	char	*substring;

	i = 0;
	j = 0;
	while (str[i])
	{
		i += count_spaces(str, i);
		if (str[i] == S_QUOTE || str[i] == D_QUOTE)
			j = len_between_quotes(str, i, str[i]);
		else if (ft_strchr("|<>", str[i]))
			j = check_tokens(str, i, str[i]);
		else
			j = len_word(str, i);
		if (j < 0)
			return (NULL);
		substring = ft_substr(str, i, j);
		if (substring != NULL)
			add_token_back(tokens, create_token(substring,
					get_type(substring)));
		if (substring)
			free(substring);
		i += j;
	}
	// assign type to redirections here ? (not in parser)
	// maybe return tokens array and not just exit status ?
	return (EXIT_SUCCESS);
}