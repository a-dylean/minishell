/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:35:35 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/16 15:30:45 by atonkopi         ###   ########.fr       */
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

char	*str_replace(char *str, char *old, char *new, int old_index)
{
	char	*new_str;
	int		i;
	int		j;
	int		size;

	size = ft_strlen(str) + ft_strlen(new) - ft_strlen(old);
	new_str = malloc(size + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && j <= size)
	{
		if (!ft_strncmp(str + i, old, ft_strlen(old)) && i == old_index)
		{
			j += ft_strlcpy(new_str + j, new, ft_strlen(new) + 1);
			ft_strlcpy(new_str + j, str + i + ft_strlen(old), ft_strlen(str));
			return (new_str);
		}
		new_str[j++] = str[i++];
	}
	return (new_str);
}