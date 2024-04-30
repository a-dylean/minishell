/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:58:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/30 17:12:20 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_between_quotes(char *str, int i, char quote)
{
	int	len;

	len = 1;
	while (str[i + len] != quote && str[i + len])	
		len++;
	len++;
	return (len);
}

int	len_word(char *str, int i)
{
	int	len;

	len = 1;
	while (str[i + len] && !ft_isspace(str[i + len]))
	{
		if (str[i + len] != S_QUOTE && str[i + len] != D_QUOTE
			&& !ft_strchr("|><", str[i + len]))
			len++;
		else
			return (len);
	}
	return (len);
}

int	count_spaces(char *str, int i)
{
	int	len;

	len = 0;
	while (str[i + len] && str[i] && ft_isspace(str[i + len]))
		len++;
	return (len);
}

void	assign_type_redirections(t_token *tokens)
{
	while (tokens)
	{
		if ((tokens->type == GREAT || tokens->type == LESS
				|| tokens->type == GREATGREAT) && (tokens->next
				&& tokens->next->type == WORD))
			tokens->next->type = FILENAME;
		else if (tokens->type == LESSLESS && (tokens->next
				&& tokens->next->type == WORD))
			tokens->next->type = DELIMITER;
		tokens = tokens->next;
	}
}

int	lexer(char *str)
{
	int		i;
	int		j;
	char	*substr;
	t_token	**tokens;

	i = 0;
	j = 0;
	tokens = init_tokens();
	if (!tokens)
	//free here
		return (0);
	while (str[i])
	{
		i += count_spaces(str, i);
		if (str[i] == S_QUOTE || str[i] == D_QUOTE)
			j = len_between_quotes(str, i, str[i]);
		else if (ft_strchr("|<>", str[i]))
			j = len_between_tokens(str, i, str[i]);
		else
			j = len_word(str, i);
		if (j < 0)
			return (0);
		substr = ft_substr(str, i, j);
		if (substr != NULL)
			add_token_back(tokens, create_token(substr, get_type(substr)));
		if (substr)
			free(substr);
		i += j;
	}
	assign_type_redirections(*tokens);
	t_token *temp = *tokens;
	while (temp)
	{
		printf("Token: %s\nToken type: %d\n", temp->value, temp->type);
		temp = temp->next;
	}
	if (!check_syntax(*tokens))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
