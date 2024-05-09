/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:35:35 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/09 18:55:18 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	count_chars(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	char_is_separator(char c)
{
	return (c == '$' || c == ' ' || c == '=' || c == '\0' || c == D_QUOTE
		|| c == S_QUOTE);
}

int	count_spaces(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i + len] && str[i] && ft_isspace(str[i + len]))
		len++;
	return (len);
}