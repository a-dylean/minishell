/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:34:18 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/23 13:10:49 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_builtin(t_command *commands)
{
	if (ft_strcmp(commands->cmd_name[0], "cd") == 0)
		ft_cd(commands);
	else if (ft_strcmp(commands->cmd_name[0], "pwd") == 0)
	 	ft_pwd();
	// else if (ft_strcmp(commands->cmd_name[0], "echo") == 0)
	// 	ft_echo(commands);
	// else if (ft_strcmp(commands->cmd_name[0], "export") == 0)
	// 	ft_export();
	// else if (ft_strcmp(commands->cmd_name[0], "unset") == 0)
	// 	ft_unset();
	// else if (ft_strcmp(commands->cmd_name[0], "env") == 0)
	// 	ft_env();
	else if (ft_strcmp(commands->cmd_name[0], "exit") == 0)
		ft_exit(commands);
}

// simple loop for testing purposes, does not handle pipes
void	executer(t_command *commands)
{
	t_command	*current;

	current = commands;
	while (current)
	{
		if (current->is_builtin)
			exec_builtin(current); // handles the builtins 
		// else
		// 	exec_cmd(current); // will execute the other commands
		current = current->next;
	}
}