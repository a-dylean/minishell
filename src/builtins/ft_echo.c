/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:33:34 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/26 12:35:27 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_echo_flag(char *flag)
{
	int	i;

	i = 1;
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(char **cmd)
{
	bool	n_flag;
	int		i;

	n_flag = false;
	i = 1;
	if (!cmd[i])
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	else if (cmd[i] && cmd[i][0] == '-')
	{
		n_flag = check_echo_flag(cmd[1]);
		if (n_flag)
			i++;
	}
	while (cmd[i])
    {
        write(STDOUT_FILENO, cmd[i], strlen(cmd[i]));
        i++;
    }
    if (!n_flag)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}
