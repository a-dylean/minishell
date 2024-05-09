/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:38:16 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/09 15:17:08 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	var_exists(t_env *env_head, char *var_name)
{
	t_env	*env;

	env = env_head;
	if (!var_name)
		return (0);
	while (env)
	{
		if (ft_strcmp(env->var_name, var_name) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	delete_env_var(t_env *env_head, char *var_name)
{
	t_env	*env;
	t_env	*prev;

	env = env_head;
	prev = NULL;
	while (env)
	{
		if (ft_strcmp(env->var_name, var_name) == 0)
		{
			if (prev)
				prev->next = env->next;
			else
				env_head = env->next;
			free(env->var_name);
			free(env->value);
			free(env);
			return ;
		}
		prev = env;
		env = env->next;
	}
}

int	ft_unset(char **cmd, t_shell *shell)
{
	int i;

	if (!cmd[1])
		return (EXIT_SUCCESS);
	i = 1;
	while (cmd[i])
	{
		if (!is_valid_identifier(cmd[i]))
			return (write_error("unset", "not a valid identifier"), 1);
		if (var_exists(shell->env_head, shell->commands->cmd_name[i]))
			delete_env_var(shell->env_head, shell->commands->cmd_name[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
