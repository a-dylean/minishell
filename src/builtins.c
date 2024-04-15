/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:10:39 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/15 15:32:49 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo()
{

}

int	ft_cd(char *path)
{
	if (chdir(path) == -1)
		perror("chdir()");
	//handle free and error processes
}

int	ft_pwd()
{
	char	cwd[4096]; // = PATH_MAX on the system (getconf -a PATH_MAX)

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd()");
	//handle free and error processes
	ft_putstr_fd(cwd, STDOUT_FILENO);
}

int	ft_export()
{

}

int	ft_unset()
{

}

int	ft_env()
{

}

int	ft_exit()
{
	
}
