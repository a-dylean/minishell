/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:21:59 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/15 17:44:24 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* function that extracts value of env from string */

char	*get_env_from_str(char *str)
{
	int		i;
	char	*env_var;

	i = 1;
	while (str[i] && str[i] != '$' && ((ft_isalnum(str[i]) || str[i] == '_')))
		i++;
	env_var = ft_substr(str, 1, i - 1);
	if (env_var)
		return (env_var);
	return (NULL);
}
/*used in ft_cd, changes the value of OLDPWD and PWD*/
void ft_setenv(t_env *env_head, char *name, char *value)
{
	t_env *current = env_head;
	t_env *prev = NULL;

	while (current != NULL)
	{
		if (ft_strcmp(current->var_name, name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		prev = current;
		current = current->next;
	}
	return ;
}