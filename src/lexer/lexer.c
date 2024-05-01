/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:58:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/30 18:33:27 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	len_between_quotes(char *str, int i, char quote)
// {
// 	int	len;

// 	len = 1;
// 	while (str[i + len] != quote && str[i + len])	
// 		len++;
// 	len++;
// 	return (len);
// }

int	len_word(char *str, int i)
{
	int	len;

	len = 1;
	while (str[i + len] && !ft_isspace(str[i + len]))
	{
		if (!ft_strchr("|><", str[i + len]))
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
		if ((tokens->type >= LESS && tokens->type <= GREATGREAT) && (tokens->next
				&& tokens->next->type == WORD))
			tokens->next->type = FILENAME;
		else if (tokens->type == LESSLESS && (tokens->next
				&& tokens->next->type == WORD))
			tokens->next->type = DELIMITER;
		tokens = tokens->next;
	}
}

void tokenize(char *str, t_shell *shell)
{
	int		i;
	int		j;
	char	*substr;

	i = 0;
	j = 0;
	while (str[i])
	{
		i += count_spaces(str, i);
		// if (str[i] == S_QUOTE || str[i] == D_QUOTE)
		// 	j = len_between_quotes(str, i, str[i]);
		// else 
		if (ft_strchr("|<>", str[i]))
			j = len_between_tokens(str, i, str[i]);
		else
			j = len_word(str, i);
		if (j < 0)
			return ;
		substr = ft_substr(str, i, j);
		if (substr != NULL)
			add_token_back(&shell->tokens, create_token(substr, get_type(substr)));
		if (substr)
			free(substr);
		i += j;
	}

}

int	lexer(t_shell *shell)
{
	if (!shell->input)
		exit(EXIT_FAILURE);
	else if (ft_strcmp(shell->input, "\0") == 0)
		return (EXIT_FAILURE);
	else if (!valid_quotes(shell->input))
	{
		// free_shell(shell);
		printf("Error: invalid quotes\n");
		return (EXIT_FAILURE);
	}
	else if (str_is_empty_or_space_only(shell->input))
		return (EXIT_SUCCESS);
	add_history(shell->input);
	tokenize(shell->input, shell);
	assign_type_redirections(shell->tokens);
	if (!check_syntax(shell->tokens))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
