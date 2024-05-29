/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:05:44 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/22 16:12:01 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

int	invalid_arg(int argc)
{
	if (argc != 1)
		return (write_error(NULL, "minishell doesn't take any arguments", NULL),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argv;
	if (invalid_arg(argc) || init_shell(&shell, env))
		free_and_exit_shell(NULL, EXIT_FAILURE);
	minishell_loop(&shell);
	free_and_exit_shell(&shell, shell.exit_status);
	return (0);
}
