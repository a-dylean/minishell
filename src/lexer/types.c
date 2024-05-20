/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:35:58 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/20 18:54:43 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	check_redir_type(char *str, int i, int count, char ch)
{
	int	result_double;
	int	result_single;

	result_double = -1;
	result_single = -1;
	if (ch == '>')
	{
		result_double = GREATGREAT;
		result_single = GREAT;
	}
	else if (ch == '<')
	{
		result_double = LESSLESS;
		result_single = LESS;
	}
	count = i;
	while (str[count] == ch)
		count++;
	if (count - i == 2)
		return (result_double);
	else if (count - i == 1)
		return (result_single);
	return (-1);
}

int	get_type(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (PIPE);
		else if (str[i] == '>')
			return (check_redir_type(str, i, count, '>'));
		else if (str[i] == '<')
			return (check_redir_type(str, i, count, '<'));
		else
			return (WORD);
		i++;
	}
	return (-1);
}
