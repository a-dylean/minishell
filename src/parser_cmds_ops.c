/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmds_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:22:28 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/15 13:04:03 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"  

t_command	*init_command(void)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
		exit(EXIT_FAILURE);
	new_command->cmd_name = NULL;
	new_command->out = NULL;
	new_command->in = NULL;
	new_command->delimiter = NULL;
	new_command->env = NULL;
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
		new_node->next = NULL;
	}
	else
	{
		*commands = new_node;
		(*commands)->next = NULL;
	}
}
