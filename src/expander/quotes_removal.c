/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:34:58 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/22 14:58:58 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_unquoted_value(char *str)
{
	char	*new_str;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = 0;
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (get_quote(&quote, str[i]) && str[i] != quote)
			new_str[j++] = str[i];
		i++;
	}
	return (new_str);
}

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

void	remove_dollar_sign(t_token **token)
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
}

void	remove_quotes(t_token *tokens)
{
	t_token	*temp;
	char	*unquoted_value;

	temp = tokens;
	while (temp)
	{
		if (temp->value)
		{
			remove_dollar_sign(&temp);
			unquoted_value = get_unquoted_value(temp->value);
			if (unquoted_value)
			{
				free(temp->value);
				temp->value = unquoted_value;
			}
		}
		temp = temp->next;
	}
}
