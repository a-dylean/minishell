/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:34:58 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/10 13:28:12 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*remove_char(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], ft_strlen(str) - i);
		}
		i++;
	}
	return (str);
}

int	nested_quotes(char *str)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*str != '\0')
	{
		if (*str == S_QUOTE)
			single_quote++;
		else if (*str == D_QUOTE)
			double_quote++;
		if ((single_quote % 2 != 0) && (double_quote % 2 != 0))
			return (1);
		str++;
	}
	return (0);
}

void	handle_nested_quotes(t_token **token)
{
	if (ft_strchr((*token)->value, S_QUOTE) > ft_strchr((*token)->value,
			D_QUOTE))
		(*token)->value = remove_char((*token)->value, D_QUOTE);
	else
		(*token)->value = remove_char((*token)->value, S_QUOTE);
}

void	remove_unquoted_chars(t_token **token)
{
	int	i;

	i = 0;
	if ((*token)->value == NULL)
		return ;
	while ((*token)->value[i])
	{
		if ((*token)->value[0] == '$' && (*token)->value[i + 1]
			&& ((*token)->value[i + 1] == D_QUOTE || (*token)->value[i
					+ 1] == S_QUOTE))
			(*token)->value = remove_char((*token)->value, '$');
		i++;
	}
	if (nested_quotes((*token)->value))
	{
		handle_nested_quotes(token);
		return ;
	}
	(*token)->value = remove_char((*token)->value, D_QUOTE);
	(*token)->value = remove_char((*token)->value, S_QUOTE);
}

void	remove_quotes(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		remove_unquoted_chars(&temp);
		temp = temp->next;
	}
}
