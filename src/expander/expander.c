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

char	*get_var_value(t_env *head, char *name)
{
	while (head)
	{
		if (ft_strcmp(head->var_name, name) == 0)
			return (head->value);
		head = head->next;
	}
	return ("");
}

/* function that returns the value of the buffer */

char	*get_value_after_expansion(char *str, t_shell *shell, int *i)
{
	char	*name;
	char	*value;
	char	*replaced;
	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		value = ft_itoa(shell->exit_status);
		replaced = str_replace(str, "$?", value, *i);
		free(value);
		return (replaced);
	}
	name = get_env_from_str(str + *i);
	if (!name)
		return (free(str), NULL);
	// printf("name: %s\n", name);
	value = get_var_value(shell->env_head, name + 1);
	replaced = str_replace(str, name, value, *i);
	*i = 0;
	// free(name);
	// free(str);
	return (replaced);
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

bool	is_limiter(char *str, int i, char quote)
{
	int	counter;

	counter = 0;
	if (quote)
		return (false);
	while (i >= 0 && ft_isspace(str[i]))
		i--;
	if (i <= 0 || str[i - 1] != '<')
		return (false);
	i--;
	while (i >= 0 && str[i] == '<')
	{
		counter++;
		i--;
	}
	return (counter == 2);
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
// void	perform_expansion(t_token *temp, t_shell *shell)
// {
// 	char	*new_value;
// 	int		i;

// 	i = 0;
// 	while (temp->value[i] && temp->value[i + 1])
// 	{
// 		update_status(&temp, temp->value[i]);
// 		if ((valid_expansion(temp->value[i], temp->value[i + 1],
// 				temp->quotes_status)))
// 		{
// 			new_value = get_value_after_expansion(temp->value, shell);
// 			free(temp->value);
// 			temp->value = new_value;
// 			if (!temp->value)
// 				return ;
// 			i = -1;
// 		}
// 		else
// 			i++;
// 	}
// }

// int	expander(t_token *tokens, t_shell *shell)
// {
// 	t_token	*temp;

// 	temp = tokens;
// 	// set_quotes_status(tokens);
// 	while (temp)
// 	{
// 		if ((temp->type == WORD || temp->type == FILENAME) && temp->value)
// 			perform_expansion(temp, shell);
// 		temp = temp->next;
// 	}
// 	remove_quotes(tokens);
// 	return (0);
// }


char *expand(char *str, t_shell *shell)
{
	int i;
	char quote;

	i = 0;
	quote = 0;
	while(str[i])
	{
		get_quote(&quote, str[i]);
		if (valid_expansion(str, i, &quote))
		{
			printf("str: %s\n", str);
			str = get_value_after_expansion(str, shell, &i);
			if (!str || !str[0])
				break;
		}
		else
			i++;
	}
	printf("str: %s\n", str);
	return (str);
}