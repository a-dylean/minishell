/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:05:44 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/23 11:07:21 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell shell;
	
	if (argc > 1 || argv[1])
	{
		ft_putstr_fd("minishell: no arguments needed\n", 2);
		return (EXIT_FAILURE);
	}
	init_shell(&shell, env);
	minishell_loop(&shell);
	// free everything
	// exit with correct exit code ?
	return (0);
}