/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:03:25 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/30 15:26:32 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	str_is_empty_or_space_only(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	valid_quotes(char *str)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (str[i])
	{
		if (str[i] == S_QUOTE && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == D_QUOTE && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	return (!(in_single_quote || in_double_quote));
}

void	set_delimiter_quote_status(t_token *token)
{
	int		i;
	t_token	*tmp;

	tmp = token;
	token->quotes_status = 0;
	while (tmp)
	{
		i = 0;
		if (tmp->type == DELIMITER)
		{
			while (tmp->value[i])
			{
				if (tmp->value[i] == D_QUOTE || tmp->value[i] == S_QUOTE)
					tmp->quotes_status = 1;
				i++;
			}
		}
		tmp = tmp->next;
	}
}

int	len_between_tokens(char *str, int i, char c)
{
	int	j;

	j = i;
	if (str[i] == c)
	{
		while (str[j] == c)
			j++;
		return (j - i);
	}
	return (0);
}

int	len_invalid_type(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i])
		&& (str[i] == '|' || str[i] == '<' || str[i] == '>'))
		i++;
	return (i);
}
