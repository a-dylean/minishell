/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:43:00 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/09 16:03:39 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_terminal()
{
	char	*buffer;

	buffer = NULL;

	while ((buffer = readline("minishell$> ")) != NULL)
	{
		if (buffer[0] != '\0')
			add_history(buffer);
		free(buffer);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
