/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:33:34 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/26 12:03:54 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// we need to handle cases such as echo -n and echo -nnnnnnnnnnnnnnnnnn, which is also valid in bash

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
        if (cmd[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (!n_flag)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}

// int	ft_echo(t_command *commands)
// {
// 	int i;
// 	bool n_flag = false;

//     // Check for -n flag
// 	if (commands->cmd_name[1] && ft_strcmp(commands->cmd_name[1], "-n") == 0)
// 	{
// 		n_flag = true;
// 		i = 2; // Start from next argument after -n
// 	}
// 	else
// 		i = 1; // Start from first argument

//     // Loop through the arguments
//     for (; commands->cmd_name[i]; i++)
//     {
//         // Print the argument
//         ft_putstr_fd(commands->cmd_name[i], STDOUT_FILENO);

//         // Print a space after the argument if it's not the last one
//         if (commands->cmd_name[i + 1])
//             ft_putchar_fd(' ', STDOUT_FILENO);
//     }

//     // Print a newline if -n flag is not set
//     if (!n_flag)
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 	return (0);
// }