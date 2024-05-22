/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:55:59 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/22 14:58:43 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_var_value(char *str, t_env *env_list, char *name,
		char *d_quoted)
{
	t_env	*temp;

	temp = env_list;
	name = name + 1;
	while (temp)
	{
		if (ft_strcmp(temp->var_name, name) == 0)
			return (temp->value);
		temp = temp->next;
	}
	if (d_quoted || ft_strcmp(str, name) != 0)
		return ("");
	return (NULL);
}

char	*get_env_from_str(char *str)
{
	int		i;
	char	*var_name;

	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_name = ft_calloc(i + 1, sizeof(char));
	if (!var_name)
		return (free(str), NULL);
	i = 0;
	var_name[i] = '$';
	while (str[++i] && (ft_isalnum(str[i]) || str[i] == '_'))
		var_name[i] = str[i];
	return (var_name);
}

char	*get_new_str_value(char *str, char *old_value, char *new_value,
		int prev_index)
{
	char	*new_str;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = ft_strlen(new_value) - ft_strlen(old_value) + ft_strlen(str);
	new_str = malloc(size + 1);
	if (!new_str)
		return (NULL);
	while (str[i] && j <= size)
	{
		if (!ft_strncmp(str + i, old_value, ft_strlen(old_value))
			&& i == prev_index)
		{
			j += ft_strlcpy(new_str + j, new_value, ft_strlen(new_value) + 1);
			ft_strlcpy(new_str + j, str + i + ft_strlen(old_value),
				ft_strlen(str));
			return (new_str);
		}
		new_str[j++] = str[i++];
	}
	return (new_str);
}

char	*get_value_after_expansion(char *str, t_shell *shell, int *i)
{
	char	*d_quoted;
	char	*var_name;
	char	*value;
	char	*new_str_value;

	d_quoted = ft_strchr(str, D_QUOTE);
	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		value = ft_itoa(shell->exit_status);
		new_str_value = get_new_str_value(str, "$?", value, *i);
		return (free(value), free(str), new_str_value);
	}
	var_name = get_env_from_str(str + *i);
	if (!var_name)
		return (free(str), NULL);
	value = get_env_var_value(str, shell->env_list, var_name, d_quoted);
	if (value == NULL && *i == 0 && ft_strcmp(str, var_name) != 0)
	{
		new_str_value = ft_strtrim(str, var_name);
		return (free(var_name), free(str), new_str_value);
	}
	new_str_value = get_new_str_value(str, var_name, value, *i);
	*i = 0;
	return (free(var_name), free(str), new_str_value);
}
