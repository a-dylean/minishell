/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:35:35 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/16 19:38:48 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
