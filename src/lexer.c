/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:58:21 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/09 16:15:23 by jlabonde         ###   ########.fr       */
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
	encode_tokens(tokens);
    return (0);
}

t_token	*create_token(char *value, int key)
{
	t_token *token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->value = value;
	token->key = key;
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

int	check_special_char(char **str, int i, int j)
{
	if (str[i][j] == '|')
		return (PIPE);
	else if (str[i][j] == '<' && str[i][j + 1] != '<')
		return (IN_DIR);
	else if (str[i][j] == '>' && str[i][j + 1] != '>')
		return (OUT_DIR);
	else if (str[i][j] == '>' && str[i][j + 1] == '>')
		return (APPEND);
	else if (str[i][j] == '<' && str[i][j + 1] == '<')
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

	i = 0;
	j = 0;
	quoted = -1;
	key = -1;
	value = NULL;
	tokens = create_token(str[i], check_special_char(str, i ,j));
	while(str[++i])
	{
		temp = create_token(str[i], check_special_char(str, i ,j));
		ft_add_node_back(tokens, temp);
	}
	// join commands into array of strings (everything that is before a pipe and delimiter)
	// check for quotes after that
	// char	**commands;
	// i = 0;
	// commands = ft_calloc(150, sizeof(char *));
	// commands[i] = ft_calloc(150, sizeof(char));
	// while (tokens) {
    //     if (tokens->key != PIPE) {
    //         strcpy(commands[i] + j , tokens->value);
    //         printf("i: %d, string: %c\n", i, commands[i][j]);
    //         j += strlen(tokens->value);
    //         tokens = tokens->next;
    //     } else {
    //         commands[i][j] = '\0'; // Null-terminate the string
    //         i++;
    //         j = 0;
    //         tokens = tokens->next;
    //         if (tokens) {
    //             commands[i] = ft_calloc(100, sizeof(char));
    //         }
    //     }
    // }
	// commands[i][j] = '\0';
	
	while(tokens)
	{
		printf("key: %d, value: %s\n", tokens->key, tokens->value);
		tokens = tokens->next;
	}
	return (0);
}