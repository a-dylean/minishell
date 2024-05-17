/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/17 13:56:12 by atonkopi         ###   ########.fr       */
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

	temp = tokens;
	while (temp)
	{
		// if (ft_strchr(temp->value, S_QUOTE) == NULL && ft_strchr(temp->value,
		// 		D_QUOTE) == NULL)
		// 	temp->quotes_status = NONE;
		// else if (ft_strchr(temp->value, D_QUOTE) == NULL
		// 	&& ft_strrchr(temp->value, S_QUOTE) > ft_strchr(temp->value,
		// 		'$'))
		// 	temp->quotes_status = SQUOTED;
		// else if (ft_strchr(temp->value, S_QUOTE) == NULL
		// 	&& ft_strchr(temp->value, D_QUOTE))
		// 	temp->quotes_status = DQUOTED;
		// else if (ft_strchr(temp->value, S_QUOTE) < ft_strchr(temp->value,
		// 		D_QUOTE))
		// 	temp->quotes_status = SQUOTED;
		// else
		// 	temp->quotes_status = DQUOTED;
		// printf("token: %s\n", temp->value);
		// printf("quotes status set: %d\n", temp->quotes_status);
		temp = temp->next;
	}
}

int	valid_expansion(char c, char next_c, int quotes_status)
{
	(void)quotes_status;
	return (c == '$' && (ft_isalpha(next_c) || next_c == '?' || next_c == '_')
		&& (quotes_status == NONE || quotes_status == DQUOTED));
}
int	var_between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (1);
		else
			return (0);
	}
	return (0);
}

void	update_status(t_token **token_node, char c)
{
	if (c == '\'' && (*token_node)->quotes_status == NONE)
		(*token_node)->quotes_status = SQUOTED;
	else if (c == '\"' && (*token_node)->quotes_status == NONE)
		(*token_node)->quotes_status = DQUOTED;
	else if (c == '\'' && (*token_node)->quotes_status == SQUOTED)
		(*token_node)->quotes_status = NONE;
	else if (c == '\"' && (*token_node)->quotes_status == DQUOTED)
		(*token_node)->quotes_status = NONE;
}
void	perform_expansion(t_token *temp, t_shell *shell)
{
	char	*new_value;
	int		i;

	i = 0;
	while (temp->value[i] && temp->value[i + 1])
	{
		update_status(&temp, temp->value[i]);
		if ((valid_expansion(temp->value[i], temp->value[i + 1],
				temp->quotes_status)))
		{
			new_value = get_value_after_expansion(temp->value, shell);
			free(temp->value);
			temp->value = new_value;
			if (!temp->value)
				return ;
			i = -1;
		}
		else
			i++;
	}
}

int	expander(t_token *tokens, t_shell *shell)
{
	t_token	*temp;

	temp = tokens;
	// set_quotes_status(tokens);
	while (temp)
	{
		if ((temp->type == WORD || temp->type == FILENAME) && temp->value)
			perform_expansion(temp, shell);
		temp = temp->next;
	}
	remove_quotes(tokens);
	return (0);
}
