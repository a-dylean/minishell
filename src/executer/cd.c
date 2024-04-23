/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:44:36 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/23 12:44:54 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char *path) // takes the path to the directory to change to as argument
{
	printf("path: %s\n", path);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
