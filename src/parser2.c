/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:15:26 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/15 11:32:16 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minishell.h"

// t_command	*get_new_command(t_token *tokens)
// {
// 	t_command	*command;
// 	command = init_command();
// 	handle_redirections(tokens, command);
// 	// t_token *temp = tokens;
// 	// while(temp)
// 	// {
// 	// 	printf("Token: %s\n", temp->value);
// 	// 	temp = temp->next;
// 	// }
// 	command->cmd_name = get_cmd_from_tokens(tokens);
// 	return (command);
// }

// int	j_parser(t_token *tokens)
// {
// 	t_command	**commands;
// 	t_token		*temp;

// 	temp = tokens;
// 	commands = (t_command **)malloc(sizeof(t_command));
// 	if (!commands)
// 		return (1);
// 	*commands = NULL;
// 	while (temp)
// 	{
// 		if (temp->type == PIPE)
// 		{
// 			add_command_back(commands, get_new_command(tokens));
// 		}
// 	}
// }