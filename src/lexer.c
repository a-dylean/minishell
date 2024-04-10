/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:58:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/10 16:20:24 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_quotes(char *str)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;
	int	result;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == S_QUOTE)
			in_single_quote = !in_single_quote;
		else if (str[i] == D_QUOTE)
			in_double_quote = !in_double_quote;
		i++;
	}
	result = !(in_single_quote || in_double_quote);
	return (result);
}

t_token	*create_token(char *value, int type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*ft_get_last_node(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_add_node_back(t_token **tokens, t_token *new_node)
{
	t_token	*temp;

	if (!new_node)
		return ;
	if (*tokens && new_node)
	{
		temp = ft_get_last_node(*tokens);
		temp->next = new_node;
		new_node->next = NULL;
	}
	else
	{
		*tokens = new_node;
		(*tokens)->next = NULL;
	}
}

int	get_type(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (PIPE);
		else if (str[i] == '>' && str[i + 1] == '>')
			return (GREATGREAT);
		else if (str[i] == '<' && str[i + 1] == '<')
			return (LESSLESS);
		else if (str[i] == '<')
			return (LESS);
		else if (str[i] == '>')
			return (GREAT);
		else
			return (WORD);
		i++;
	}
	return (-1);
}
int	len_between_quotes(char *str, int i, char quote)
{
	int	len;

	len = 1;
	while (str[i + len] != quote)
		len++;
	len++;
	return (len);
}

int	len_word(char *str, int i)
{
	int	len;

	len = 1;
	while (!ft_isspace(str[i + len]) && str[i + len] && str[i + len] != S_QUOTE
		&& str[i + len] != D_QUOTE)
		len++;
	return (len);
}

int	count_spaces(char *str, int i)
{
	int	len;

	len = 0;
	while (ft_isspace(str[i + len]) && str[i])
		len++;
	return (len);
}
t_token	*encode_tokens(char *str)
{
	int		i;
	int		j;
	t_token	**tokens;
	char	*substring;

	i = 0;
	j = 0;
	if (!valid_quotes(str))
	{
		printf("Error: invalid quotes\n");
		return (NULL);
	}
	tokens = (t_token **)malloc(sizeof(t_token));
	*tokens = NULL;
	while (str[i])
	{
		i += count_spaces(str, i);
		if (str[i] == S_QUOTE || str[i] == D_QUOTE)
			j = len_between_quotes(str, i, str[i]);
		else
			j = len_word(str, i);
		substring = ft_substr(str, i, j);
		ft_add_node_back(tokens, create_token(substring, get_type(substring)));
		i += j;
	}
	while (*tokens)
	{
		printf("type: %d, value: %s\n", (*tokens)->type, (*tokens)->value);
		tokens = &(*tokens)->next;
	}
	return (*tokens);
}
