/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:58:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/09 12:50:52 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int valid_quotes(char *str)
{
    int i;
    int in_single_quote = 0;
    int in_double_quote = 0;
    int result;

    i = 0;
    while(str[i])
    {
        if (str[i] == '\'')
            in_single_quote = !in_single_quote;
        else if (str[i] == '\"')
            in_double_quote = !in_double_quote;
        i++;
    }
    result = !(in_single_quote || in_double_quote);
    return result;
}

int get_tokens(char *str)
{
    int i;
    int j;
    char **tokens;

    i = 0;
    j = 0;
    tokens = ft_split_charset(str, " \t\r\v\f\n");
    while (tokens[i])
    {
        printf("Token %d: %s\n", i, tokens[i]);
        i++;
    }
    return (0);
}

t_token	*create_token(char *value, int key, int quoted)
{
	t_token *token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->value = value;
	token->key = key;
	token->quoted = quoted;
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

void	ft_add_node_back(t_token *tokens, t_token *new_node)
{
	t_token	*temp;

	if (!new_node)
		return ;
	if (tokens && new_node)
	{
		temp = ft_get_last_node(tokens);
		temp->next = new_node;
		new_node->next = NULL;
	}
	else
	{
		tokens = new_node;
		(tokens)->next = NULL;
	}
}
// t_token	*ft_lstlast(t_token *lst)
// {
// 	t_token	*temp;

// 	if (!lst)
// 		return (NULL);
// 	temp = lst;
// 	while (temp->next)
// 		temp = temp->next;
// 	return (temp);
// }

// void	ft_lstadd_back(t_token **lst, t_token *new)
// {
// 	t_token	*back;

// 	if (!lst || !new)
// 		return ;
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	back = ft_lstlast(*lst);
// 	back->next = new;
// }

int	check_special_char(char **str, int i, int j)
{
	if (str[i][j] == '|')
		return (PIPE);
	else if (str[i][j] == '<' && str[i][j + 1] && str[i][j + 1] != '<')
		return (IN_DIR);
	else if (str[i][j] == '>' && str[i][j + 1] && str[i][j + 1] != '>')
		return (OUT_DIR);
	else if (str[i][j] == '>' && str[i][j + 1] && str[i][j + 1] == '>')
		return (APPEND);
	else if (str[i][j] == '<' && str[i][j + 1] && str[i][j + 1] == '<')
		return (DELIMITER);
	else if (str[i][j] == '$')
		return (DOLLAR);
	else if (str[i][j] == '-')
		return (FLAG);
	else
		return (CMD);
}

int	encode_tokens(char **str)
{
	int	i;
	int	j;
	int	quoted;
	int	key;
	char *value;
	t_token	*tokens;
	t_token *temp;

	i = -1;
	j = 0;
	quoted = -1;
	key = -1;
	value = NULL;
	tokens = (t_token *)malloc(sizeof(t_token));
	if (!tokens)
		exit(EXIT_FAILURE);
	
	while(str[++i])
	{
		temp = create_token(str[i], check_special_char(str, i ,j), 0);
		ft_add_node_back(tokens, temp);
	}
	i = 0;
	while(tokens)
	{
		printf("key: %d, value: %s/n", tokens->key, tokens->value);
		i++;
	}
	return (0);
}