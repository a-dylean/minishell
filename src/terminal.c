/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:43:00 by jlabonde          #+#    #+#             */
/*   Updated: 2024/04/08 12:37:53 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_terminal()
{
	char	*buffer;

	buffer = NULL;

	//read lines written by the user and store them into buffer
	// the readline function uses malloc, so buffer does not need to be allocated
	// BUT it needs to be freed
	while ((buffer = readline("minishell$> ")) != NULL)
	{
		// we don't want to store empty lines in the history, bash does not
		if (buffer[0] != '\0')
			add_history(buffer);
		free(buffer);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
