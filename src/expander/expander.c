/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/20 14:00:45 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_expansion(char *str, int i, char *quote)
{
	if (*quote == S_QUOTE)
		return (0);
	if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i
			+ 1] == '?'))
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

int	get_quote(char *quote, char c)
{
	if (c == S_QUOTE || c == D_QUOTE)
	{
		if (*quote == 0)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
		return (*quote);
	}
	return (-1);
}

char	*expander(char *str, t_shell *shell)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		get_quote(&quote, str[i]);
		if (valid_expansion(str, i, &quote))
		{
			str = get_value_after_expansion(str, shell, &i);
			if (!str || !str[0])
				break ;
		}
		else
			i++;
	}
	return (str);
}