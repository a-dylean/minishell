/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:34:58 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/14 12:21:59 by jlabonde         ###   ########.fr       */
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

void remove_unquoted_chars(t_token **token)
{
	if ((*token)->value == NULL)
		return ;
	if ((*token)->quotes_status == NONE)
	{
		(*token)->value = remove_char((*token)->value, D_QUOTE);
		(*token)->value = remove_char((*token)->value, S_QUOTE);
	}
	else if ((*token)->quotes_status == DQUOTED)
	{
		(*token)->value = remove_char((*token)->value, D_QUOTE);
	}
	else if ((*token)->quotes_status == SQUOTED)
	{
		(*token)->value = remove_char((*token)->value, S_QUOTE);
	}
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
