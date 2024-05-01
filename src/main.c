/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:05:44 by atonkopi          #+#    #+#             */
/*   Updated: 2024/04/30 18:34:39 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	invalid_arg(t_shell *shell, int argc, char **argv)
{
	if (argc != 1 && argc != 3)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("wrong arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (argc == 3)
	{
		shell->interactive = 0;
		if (!argv[1] || (argv[1] && ft_strcmp(argv[1], "-c") != 0))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd("invalid option\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		else if (!argv[2] || (argv[2] && argv[2][0] == '\0'))
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd("no command provided\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	else
		shell->interactive = 1;
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_shell shell;
	if (init_shell(&shell, env) || invalid_arg(&shell, argc, argv))
		exit_shell(NULL, EXIT_FAILURE);
	if (shell.interactive)
		minishell_loop(&shell);
	else
		non_interactive_behaviour(&shell, argv[2]);
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 6);
	exit_shell(&shell, g_exit_code);
	return (0);
}