/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:23:54 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/14 12:40:45 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	process_commands(t_command *commands, bool *n_flag, int *i)
{
	int	j;

	while (commands->cmd_name[*i] && commands->cmd_name[*i][0] == '-')
	{
		j = 1;
		while (commands->cmd_name[*i][j] == 'n')
			j++;
		if (commands->cmd_name[*i][j] == '\0')
			*n_flag = true;
		else
			break ;
		(*i)++;
	}
}

static void	write_commands(t_command *commands, bool n_flag, int *i)
{
	while (commands->cmd_name[*i])
	{
		write(STDOUT_FILENO, commands->cmd_name[*i],
			ft_strlen(commands->cmd_name[*i]));
		if (commands->cmd_name[*i + 1] && !ft_strcmp(commands->cmd_name[*i], ""))
			write(STDOUT_FILENO, " ", 1);
		(*i)++;
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
}

int	ft_echo(t_command *commands)
{
	bool	n_flag;
	int		i;

	n_flag = false;
	i = 1;
	if (!commands->cmd_name[i])
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	process_commands(commands, &n_flag, &i);
	write_commands(commands, n_flag, &i);
	return (0);
}
