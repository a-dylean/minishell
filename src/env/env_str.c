/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:21:59 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/17 13:44:15 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*used in ft_cd, changes the value of OLDPWD and PWD*/
void	ft_setenv(t_env *env_head, char *name, char *value)
{
	t_env	*current;
	// t_env	*prev;

	current = env_head;
	// prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->var_name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		// prev = current;
		current = current->next;
	}
	return ;
}
