/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:43:00 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/11 14:23:37 by atonkopi         ###   ########.fr       */
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
		//encode_tokens(buffer);
		free(buffer);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
