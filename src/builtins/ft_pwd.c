/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:10:39 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/29 13:45:49 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_command *commands)
{
	char	cwd[4096];

	if (commands->cmd_name[1] && commands->cmd_name[1][0]
			&& commands->cmd_name[1][0] == '-')
	{
		write_error(commands->cmd_name[1], "invalid option", NULL);
		return (2);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putstr_fd("pwd: error retrieving ", STDERR_FILENO);
		perror("current directory: getcwd: cannot access parent directories");
		return (1);
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
