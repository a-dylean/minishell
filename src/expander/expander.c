/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/15 17:37:13 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void update_quotes_status(t_token **token, char c)
{
	if (c == S_QUOTE && (*token)->quotes_status == NONE)
		(*token)->quotes_status = SQUOTED;
	else if (c == D_QUOTE && (*token)->quotes_status == NONE)
		(*token)->quotes_status = DQUOTED;
	else if (c == S_QUOTE && (*token)->quotes_status == SQUOTED && (*token)->value[(int)ft_strlen((*token)->value) - 1] != c)
		(*token)->quotes_status = NONE;
	else if (c == D_QUOTE && (*token)->quotes_status == DQUOTED && (*token)->value[(int)ft_strlen((*token)->value) - 1] != c)
		(*token)->quotes_status = NONE;
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
	int i;

	// tokens or shell->tokens ?
	temp = shell->tokens;
	while (temp)
	{
		i = 0;
		while (temp->value[i])
		{
			update_quotes_status(&temp, temp->value[i]);
			i++;
		}
		if ((temp->type == WORD || temp->type == FILENAME) && temp->value)
			perform_expansion(temp, shell);
		
		temp = temp->next;
	}
	remove_quotes(tokens);
	return (0);
}
