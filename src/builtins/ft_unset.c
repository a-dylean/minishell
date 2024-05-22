/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:38:16 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/22 16:26:57 by jlabonde         ###   ########.fr       */
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
	int	i;

	if (!cmd[1])
		return (EXIT_SUCCESS);
	i = 1;
	while (cmd[i])
	{
		if (cmd[1][0] == '-')
			return (write_error(cmd[1], "invalid option", "export"), 2);
		if (var_exists(shell->env_list, shell->commands->cmd_name[i]))
			delete_env_var(shell->env_list, shell->commands->cmd_name[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
