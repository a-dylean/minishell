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

/* function that extracts value of env from string */

char	*get_env_from_str(char *str)
{
	int		i;
	char	*env_var;
	
	// printf("str ENV: %s\n", str);
	// if (ft_strchr(str, S_QUOTE))
	// {
	// 	env_var = ft_strtrim(str, "\'");
	// 	if (env_var)
	// 		return (env_var);
	// 	return (NULL);
	// }
	i = 1;
	while (str[i] && str[i] != '$' && ((ft_isalnum(str[i]) || str[i] == '_')))
		i++;
	env_var = ft_substr(str, 1, i - 1);
	if (env_var)
		return (env_var);
	return (NULL);
}
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
