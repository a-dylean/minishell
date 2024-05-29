/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:54:45 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/29 13:55:05 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_and_return(char *curr_dir, char *old_dir, int ret)
{
	if (curr_dir)
		free(curr_dir);
	if (old_dir)
		free(old_dir);
	return (ret);
}

int	handle_chdir_error(char *curr_dir, char *old_dir)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	perror(old_dir);
	return (free_and_return(curr_dir, old_dir, 1));
}
