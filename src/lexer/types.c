/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:35:58 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/23 16:26:42 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	check_pipe_type(char *str, int i, int count)
{
	count = i;
	while (str[count] == '|')
		count++;
	if (count - i != 1)
		return (-1);
	return (PIPE);
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
			return (check_pipe_type(str, i, count));
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

void	assign_type_redirections(t_token *tokens)
{
	while (tokens)
	{
		if ((tokens->type >= LESS && tokens->type <= GREATGREAT)
			&& (tokens->next && tokens->next->type == WORD))
			tokens->next->type = FILENAME;
		else if (tokens->type == LESSLESS && (tokens->next
				&& tokens->next->type == WORD))
			tokens->next->type = DELIMITER;
		tokens = tokens->next;
	}
}
