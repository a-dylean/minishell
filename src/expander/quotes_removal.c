/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_removal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:34:58 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/06 13:08:15 by jlabonde         ###   ########.fr       */
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

void	remove_unquoted_chars(t_token **token, char *new_value)
{
	// if (ft_strlen((*token)->value) == 2)
	// {
	// 	new_value = ft_strdup("\'\'");
	// 	(*token)->value = new_value;
	// }
	// else 
	if ((*token)->quotes_status == NONE)
	{
		new_value = remove_char((*token)->value, D_QUOTE);
		new_value = remove_char(new_value, S_QUOTE);
		(*token)->value = new_value;
	}
	else if ((*token)->quotes_status == DQUOTED)
	{
		new_value = remove_char((*token)->value, D_QUOTE);
		(*token)->value = new_value;
	}
	else if ((*token)->quotes_status == SQUOTED)
	{
		new_value = remove_char((*token)->value, S_QUOTE);
		(*token)->value = new_value;
	}
}

void	remove_quotes(t_token *tokens)
{
	t_token	*temp;
	char	*new_value;

	temp = tokens;
	new_value = NULL;
	while (temp)
	{
		remove_unquoted_chars(&temp, new_value);
		temp = temp->next;
	}
	free(new_value);
}
