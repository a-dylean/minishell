/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_global.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:45:38 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/14 14:58:46 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_node(t_env *env)
{
	if (env->var_name)
		free(env->var_name);
	if (env->value)
		free(env->value);
	if (env)
		free(env);
}

void	free_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		free_env_node(current);
		current = next;
	}
}

char	*ft_getenv(t_env *env_list, char *key)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->var_name, key) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
