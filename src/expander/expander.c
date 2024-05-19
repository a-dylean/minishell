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

char	*get_var_value(t_env *head, char *name, char *d_quoted)
{
	while (head)
	{
		if (ft_strcmp(head->var_name, name) == 0)
			return (head->value);
		head = head->next;
	}
	if (d_quoted)
		return ("");
	return (NULL);
}

/* function that returns the value of the buffer */

char	*get_value_after_expansion(char *str, t_shell *shell, int *i)
{
	char	*name;
	char	*value;
	char	*replaced;
	char	*d_quoted;

	d_quoted = ft_strchr(str, D_QUOTE);
	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		value = ft_itoa(shell->exit_status);
		replaced = str_replace(str, "$?", value, *i);
		return (free(value), free(str), replaced);
	}
	name = get_env_from_str(str + *i);
	if (!name)
		return (free(str), NULL);
	value = get_var_value(shell->env_list, name + 1, d_quoted);
	if (!value)
		return (free(name), free(str), NULL);
	replaced = str_replace(str, name, value, *i);
	*i = 0;
	return (free(name), free(str), replaced);
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

int	valid_expansion(char *str, int i, char *quote)
{
	if (*quote == S_QUOTE)
		return (0);
	if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

void	perform_expansion(t_token *temp, t_shell *shell)
{
	int		i;
	char quote;

	i = 0;
	quote = 0;
	while (temp->value[i])
	{
		get_quote(&quote, temp->value[i]);
		if (valid_expansion(temp->value, i, &quote))
		{
			temp->value = get_value_after_expansion(temp->value, shell, &i);
			if (!temp->value || !temp->value[0])
				break ;
		}
		else
			i++;
	}
}

int	expander(t_token *tokens, t_shell *shell)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if ((temp->type == WORD || temp->type == FILENAME) && temp->value)
			perform_expansion(temp, shell);
		temp = temp->next;
	}
	remove_quotes(tokens);
	return (0);
}