/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/22 14:58:22 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_heredoc(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] == '<' && str[i + 1] == '<')
			return (1);
		if (str[i])
			i++;
	}
	return (0);
}

int	valid_expansion(char *str, int i, char *quote)
{
	if (*quote == S_QUOTE)
		return (0);
	if (str && is_heredoc(str))
		return (0);
	if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
			|| str[i + 1] == '?'))
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

int	count_dollars(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*expander(char *str, t_shell *shell)
{
	int		i;
	char	quote;
	int		expansions_counter;

	i = 0;
	quote = 0;
	expansions_counter = count_dollars(str);
	while (str[i])
	{
		get_quote(&quote, str[i]);
		if (valid_expansion(str, i, &quote) && expansions_counter-- > 0)
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
