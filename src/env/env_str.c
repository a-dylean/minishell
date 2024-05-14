/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:21:59 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/14 14:53:52 by jlabonde         ###   ########.fr       */
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
