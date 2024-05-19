/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:05:44 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/17 14:26:31 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

int	invalid_arg(int argc)
{
	if (argc != 1)
		return (write_error(NULL, "minishell doesn't take any arguments"),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	t_shell shell;
	if (invalid_arg(argc) || init_shell(&shell, env))
		free_and_exit_shell(NULL, EXIT_FAILURE);
	minishell_loop(&shell);
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 6);
	free_and_exit_shell(&shell, g_exit_code);
	return (0);
}