/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:22:28 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/30 15:17:58 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*get_command(t_token *tokens)
{
	t_command	*command;

	if (!tokens)
		return (NULL);
	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	ft_memset(command, 0, sizeof(t_command));
	command->cmd_name = get_cmd_array_from_tokens(tokens);
	handle_redirections(tokens, command);
	if (command->cmd_name && command->cmd_name[0])
		command->is_builtin = is_builtin(command->cmd_name[0]);
	return (command);
}

t_command	*init_command(void)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
		exit(EXIT_FAILURE);
	new_command->cmd_name = NULL;
	new_command->is_builtin = false;
	return (new_command);
}

t_command	*get_last_command(t_command *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	add_command_back(t_command **commands, t_command *new_node)
{
	t_command	*temp;

	if (!new_node)
		return ;
	if (*commands && new_node)
	{
		temp = get_last_command(*commands);
		temp->next = new_node;
		new_node->prev = temp;
		new_node->next = NULL;
	}
	else
	{
		*commands = new_node;
		(*commands)->next = NULL;
		(*commands)->prev = NULL;
	}
}
