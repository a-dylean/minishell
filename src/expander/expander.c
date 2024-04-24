/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:18:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/24 15:14:26 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_quotes_status(t_token *tokens)
{
	t_token	*temp;
	int		in_single_quotes;
	int		in_double_quotes;

	temp = tokens;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (temp)
	{
		if (temp->value[0] == S_QUOTE && temp->quotes_status != DQUOTED)
			in_single_quotes = !in_single_quotes;
		else if (temp->value[0] == D_QUOTE && temp->quotes_status != SQUOTED)
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

int	expander(t_token *tokens, t_shell *shell)
{
	t_token	*temp;
	int		i;

	(void)shell;
	temp = tokens;
	set_quotes_status(temp);
	while (temp)
	{
		// printf("TOKEN[%d]\ntemp->value: %s\ntemp->type: %d\ntemp->quotes:
		// %d\n", temp->id, temp->value, temp->type, temp->quotes_status);
		// 	set_quotes_status(temp);
		if (temp->type == WORD || temp->type == FILENAME)
		{
			i = 0;
			while (temp->value[i])
			{
				if (temp->value[i] == '$' && temp->value[i + 1] != '\0'
					&& !char_is_separator(temp->value[i + 1])
					&& (temp->quotes_status == NONE
						|| temp->quotes_status == DQUOTED))
					replace_with_expansion(&temp, shell);
				i++;
			}
		}
		temp = temp->next;
	}
	return (0);
}

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

/* function that calculates the size of the expansion
that will be added to the buffer */

int	calculate_expansion_size(char *token, int *i)
{
	int		buffer_size;
	char	*env_var_value;
	char	*env_var;

	buffer_size = 0;
	env_var = get_env_from_str(&token[*i]);
	if (env_var_exists(env_var))
	{
		env_var_value = getenv(env_var);
		if (env_var_value)
			buffer_size += ft_strlen(env_var_value);
	}
	if (env_var)
		*i += ft_strlen(env_var) + 1;
	else
		*i += 1;
	return (buffer_size);
}
