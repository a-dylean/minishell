/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:22:53 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/06 13:27:56 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_env(t_shell *shell)
{
	t_env *env;

	env = shell->env_head;
	while (env)
	{
		printf("%s=%s\n", env->var_name, env->value);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}