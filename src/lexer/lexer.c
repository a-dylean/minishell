/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:58:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/09 19:01:16 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	get_token_size(char *str)
{
	int	type;
	int	i;

	if (!str)
		return (-1);
	type = get_type(str);
	if (type == GREATGREAT || type == LESSLESS)
		return (2);
	if (type == PIPE || type == LESS || type == GREAT)
		return (1);
	i = 0;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '|')
	{
		if ((str[i] == D_QUOTE || str[i] == S_QUOTE) && str[i + 1] != '\0')
			i += ft_strchr(&str[i + 1], str[i]) - &str[i] + 1;
		else
			i++;
	}
	return (i);
}

char	*get_token(char *str)
{
	char	*token_value;
	int		len;

	len = get_token_size(str);
	if (len == -1)
		return (NULL);
	token_value = ft_strndup(str, len);
	if (!token_value)
		return (NULL);
	return (token_value);
}

t_token	*tokenize(char *str, t_shell *shell)
{
	int		i;
	char	*substr;
	t_token	*new_token;

	i = 0;
	while (*str)
	{
		if (ft_isspace(*str))
			str++;
		else
		{
			substr = get_token(str);
			if (!substr)
				return (free_tokens(&shell->tokens), NULL);
			new_token = create_token(substr, get_type(substr), NONE);
			if (!new_token)
				return (free(substr), free_tokens(&shell->tokens), NULL);
			add_token_back(&shell->tokens, new_token);
			str += ft_strlen(substr);
			free(substr);
			i++;
		}
	}
	return (shell->tokens);
}

int	lexer(t_shell *shell)
{
	if (!shell->input)
		exit(EXIT_FAILURE);
	else if (ft_strcmp(shell->input, "\0") == 0)
		return (EXIT_FAILURE);
	else if (!valid_quotes(shell->input))
	{
		printf("Error: invalid quotes\n");
		return (EXIT_FAILURE);
	}
	else if (str_is_empty_or_space_only(shell->input))
		return (EXIT_SUCCESS);
	add_history(shell->input);
	shell->tokens = tokenize(shell->input, shell);
	if (!shell->tokens)
		return (EXIT_FAILURE);
	assign_type_redirections(shell->tokens);
	if (!check_syntax(shell->tokens))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
