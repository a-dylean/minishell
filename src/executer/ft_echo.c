/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:33:34 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/26 11:34:35 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// we need to handle cases such as echo -n and echo -nnnnnnnnnnnnnnnnnn, which is also valid in bash

// int		check_echo_flag(char *flag)
// {
// 	int	i;

// 	i = 0;
// 	while (flag[i])
// 	{
		
// 	}
// }

// void	ft_echo(t_command *commands)
// {
// 	bool	n_flag;
// 	int		i;

// 	n_flag = false;
// 	i = 0;
// 	if (!commands->cmd_name[1])
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		return ;
// 	}
// 	else if (commands->cmd_name[1][0] == '-')
// 	{
// 		if (commands->cmd_name[1][1] && commands->cmd_name[1][1] == 'n')
// 		{
// 			if (commands->cmd_name[1][2] == '\0')
// 				n_flag = true;
// 			// else
// 			// 	check_echo_flag(commands->cmd_name[1]);
// 		}

// 	}
// }

int	ft_echo(t_command *commands)
{
    int i;
    bool n_flag = false;

    // Check for -n flag
    if (commands->cmd_name[1] && ft_strcmp(commands->cmd_name[1], "-n") == 0)
    {
        n_flag = true;
        i = 2; // Start from next argument after -n
    }
    else
    {
        i = 1; // Start from first argument
    }

    // Loop through the arguments
    for (; commands->cmd_name[i]; i++)
    {
        // Print the argument
        ft_putstr_fd(commands->cmd_name[i], STDOUT_FILENO);

        // Print a space after the argument if it's not the last one
        if (commands->cmd_name[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
    }

    // Print a newline if -n flag is not set
    if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}