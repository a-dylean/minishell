/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:10:39 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/23 12:44:47 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// we need to handle cases such as echo -n and echo -nnnnnnnnnnnnnnnnnn, which is also valid in bash
// void	ft_echo(t_command *commands)
// {
	
// }

int	ft_pwd(void) // works with absolut path for now. Needs to work with relative path
{
	char	cwd[4096]; // = PATH_MAX on the system (getconf -a PATH_MAX)

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd");
		return (1);
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

// int	ft_export()
// {

// }

// int	ft_unset()
// {

// }

// int	ft_env()
// {

// }
