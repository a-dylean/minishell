/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/10 15:12:50 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* function that returns the value of the buffer */

char	*get_value_after_expansion(char *token, t_shell *shell)
{
	char	*new_token;
	char	*buffer;

	buffer = init_buffer(token, shell);
	if (!buffer)
		return (NULL);
	buffer = get_buffer_value(token, buffer, shell);
	if (!buffer)
		return (NULL);
	new_token = get_value_from_buffer(buffer);
	if (!new_token)
		return (free(buffer), NULL);
	free(buffer);
	return (new_token);
}

void	set_quotes_status(t_token *tokens)
{
	t_token	*temp;
	int		in_single_quotes;
	int		in_double_quotes;

	temp = tokens;
	while (temp)
	{
		in_single_quotes = 0;
		in_double_quotes = 0;
		if (temp->value[0] == S_QUOTE && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (temp->value[0] == D_QUOTE && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		if (in_single_quotes)
			temp->quotes_status = SQUOTED;
		else if (in_double_quotes)
			temp->quotes_status = DQUOTED;
		else
			temp->quotes_status = NONE;
		temp = temp->next;
	}
}

int	valid_expansion(char c, char next_c, int quotes_status)
{
	return (c == '$' && (ft_isalpha(next_c) || next_c == '?' || next_c == '_')
		&& (quotes_status == NONE || quotes_status == DQUOTED));
}

void	perform_expansion(t_token *temp, t_shell *shell)
{
	char	*new_value;
	int		i;

	i = 0;
	while (temp->value[i] && temp->value[i + 1])
	{
		if (valid_expansion(temp->value[i], temp->value[i + 1],
				temp->quotes_status))
		{
			new_value = get_value_after_expansion(temp->value, shell);
			free(temp->value);
			temp->value = new_value;
			if (!temp->value)
				return ;
			i = -1;
		}
		i++;
	}
}

int	expander(t_token *tokens, t_shell *shell)
{
	t_token	*temp;

	temp = tokens;
	set_quotes_status(tokens);
	while (temp)
	{
		if ((temp->type == WORD || temp->type == FILENAME) && temp->value)
			perform_expansion(temp, shell);
		temp = temp->next;
	}
	remove_quotes(tokens);
	return (0);
}
