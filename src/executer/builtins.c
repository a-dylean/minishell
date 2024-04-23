/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:10:39 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/22 15:52:53 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	ft_echo(char *str)
// {
// 	printf("%s\n", str);
// }

int	ft_cd(char *path) // takes the path to the directory to change to as argument
{
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	ft_pwd(void)
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



// add a function if status is NULL == if there is no n, then we need to return the last commands exit status
// now, this function deals with exit [n] where n is an optional argument, but does not deal with exit without n
int	ft_exit(char *status)
{
	long stat;

	stat = 0;
	if (status != NULL)
	{
		stat = ft_atol(status);
		if (errno == ERANGE)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(status, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			return (1);
		}
		else
		{
			if (stat > 255)
				stat = stat % 256;
			else if (stat < 0)
				stat = (stat % 256) + 256;
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			exit(stat);
		}
	}
	return (0);
}
