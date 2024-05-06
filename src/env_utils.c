/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:38:36 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/06 13:17:08 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*value_mem_alloc(char *str, size_t var_name_len)
{
	char	*value;
	size_t	full_str_len;

	full_str_len = ft_strlen(str);
	if (var_name_len + 1 == full_str_len)
	{
		value = malloc(2);
		if (!value)
			exit(EXIT_FAILURE);
		value[0] = ' ';
		value[1] = '\0';
	}
	else if (var_name_len == full_str_len)
		value = NULL;
	else
	{
		value = malloc(full_str_len - var_name_len);
		if (!value)
			exit(EXIT_FAILURE);
	}
	return (value);
}

char	*get_env_value(char *str, char *var_name)
{
	size_t	var_name_len;
	char	*value;

	var_name_len = ft_strlen(var_name);
	value = value_mem_alloc(str, var_name_len);
	if (value != NULL)
		ft_strlcpy(value, str + var_name_len + 1, ft_strlen(str)
			- var_name_len);
	return (value);
}

t_env	*init_env_node(char *str)
{
	char	**split;
	t_env	*env_node;

	env_node = malloc(sizeof(t_env));
	if (!env_node)
		return (NULL);
	split = ft_split(str, '=');
	env_node->var_name = ft_strdup(split[0]);
	env_node->value = get_env_value(str, split[0]);
	env_node->next = NULL;
	free_array(split);
	return (env_node);
}

void	add_back_env_var(t_env *head, t_env *new)
{
	t_env	*curr;

	curr = head;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

t_env	*init_env(char **env)
{
	int		i;
	t_env	*head;

	i = 0;
	head = init_env_node(env[i++]);
	while (env[i])
	{
		add_back_env_var(head, init_env_node(env[i]));
		i++;
	}
	// printing env list
	// t_env *tmp = head;
	// while (tmp)
	// {
	// 	printf("var_name: %s\n", tmp->var_name);
	// 	printf("value: %s\n", tmp->value);
	// 	tmp = tmp->next;
	// }
	return (head);
}

void	free_env_node(t_env *env)
{
	free(env->var_name);
	free(env->value);
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
