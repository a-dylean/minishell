/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/25 18:34:10 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* function that returns the value of the buffer */

char	*get_value_after_expansion(char *token, t_shell *shell)
{
	char	*new_token;
	char	*buffer;

	buffer = init_buffer(token);
	if (!buffer)
		return (NULL);
	buffer = get_buffer_value(token, buffer, shell);
	new_token = get_value_from_buffer(buffer);
	if (!new_token)
		return (NULL);
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
void	perform_expansion(t_token *tokens, t_shell *shell)
{
	t_token	*temp;
	int		i;

	temp = tokens;
	while (temp)
	{
		if (temp->type == WORD || temp->type == FILENAME)
		{
			i = -1;
			while (temp->value[++i])
			{
				if (temp->value[i] == '$' && temp->value[i + 1] != '\0'
					&& !char_is_separator(temp->value[i + 1])
					&& (temp->quotes_status == NONE
						|| temp->quotes_status == DQUOTED))
					temp->value = get_value_after_expansion(temp->value, shell);
				if (!temp || !temp->value)
					break ;
			}
		}
		if (temp)
			temp = temp->next;
	}
}
char	*delete_quotes(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], strlen(str) - i);
		}
		i++;
	}
	return (str);
}

void	remove_unquoted_chars(t_token **token, char *new_value)
{
	if (ft_strlen((*token)->value) == 2)
	{
		new_value = ft_strdup("");
		(*token)->value = new_value;
	}
	else if ((*token)->quotes_status == DQUOTED)
	{
		new_value = delete_quotes((*token)->value, D_QUOTE);
		(*token)->value = new_value;
	}
	else if ((*token)->quotes_status == SQUOTED)
	{
		new_value = delete_quotes((*token)->value, S_QUOTE);
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
		if (temp->quotes_status != NONE)
			remove_unquoted_chars(&temp, new_value);
		temp = temp->next;
	}
	free(new_value);
}

int	expander(t_token *tokens, t_shell *shell)
{
	set_quotes_status(tokens);
	perform_expansion(tokens, shell);
	remove_quotes(tokens);
	return (0);
}
