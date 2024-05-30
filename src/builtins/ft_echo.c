/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:23:54 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/30 16:50:14 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	check_for_n_flag(t_command *commands, bool *n_flag, int *i)
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

/*gets the length of the command to write, then writes it.
Separate multiple commands by one space
If the n_flag is present, does not write \n*/
static void	write_commands(t_command *commands, bool n_flag, int *i)
{
	while (commands->cmd_name[*i])
	{
		write(STDOUT_FILENO, commands->cmd_name[*i],
			ft_strlen(commands->cmd_name[*i]));
		if (commands->cmd_name[*i + 1] && commands->cmd_name[*i + 1][0] != '\0')
			write(STDOUT_FILENO, " ", 1);
		(*i)++;
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
}

/*If there is not argument, prints \n and returns.
Otherwise, checks for valid flags and writes the commands*/
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
	if (commands->cmd_name[i][0] == '-' && commands->cmd_name[i][1] == 'n')
		check_for_n_flag(commands, &n_flag, &i);
	write_commands(commands, n_flag, &i);
	return (0);
}
