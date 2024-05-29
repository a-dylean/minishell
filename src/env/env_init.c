/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:42:53 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/29 15:28:50 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*init_default_env(void)
{
	t_env	*new;
	t_env	*res;

	res = NULL;
	new = init_default_env_node("PWD", getcwd(NULL, 0));
	if (!new)
		return (free_env(res), NULL);
	add_back_env_var(&res, new);
	new = init_default_env_node("SHLVL", "1");
	if (!new)
		return (free_env(res), NULL);
	add_back_env_var(&res, new);
	new = init_default_env_node("_", "/usr/bin/env");
	if (!new)
		return (free_env(res), NULL);
	add_back_env_var(&res, new);
	add_back_env_var(&res, NULL);
	return (res);
}

t_env	*init_env(char **env)
{
	int		i;
	t_env	*head;
	t_env	*new_node;

	i = 0;
	head = NULL;
	while (env[i])
	{
		new_node = init_env_node(env[i]);
		if (!new_node)
			return (free_env(head), NULL);
		add_back_env_var(&head, new_node);
		i++;
	}
	add_back_env_var(&head, NULL);
	if (!head)
		head = init_default_env();
	return (head);
}

int	list_len(t_env *env_head)
{
	int		i;
	t_env	*current;

	i = 0;
	current = env_head;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

// char	**init_env_array(t_env *env_head)
// {
// 	int		i;
// 	t_env	*current;
// 	char	**res;
// 	char 	*tmp;

// 	i = 0;
// 	current = env_head;
// 	res = malloc(sizeof(char *) * (list_len(current) + 1));
// 	if (!res)
// 		return (NULL);
// 	while (current)
// 	{
// 		tmp = ft_strjoin(current->var_name, "=");
// 		if (!tmp)
// 			return (free_array(res), NULL);
// 		if (current->value)
// 		{
// 			res[i] = ft_strjoin(tmp, current->value);
// 			free(tmp);
// 			if (!res[i])
// 				return (free_array(res), NULL);
// 		}
// 		i++;
// 		current = current->next;
// 	}
// 	res[i] = NULL;
// 	return (res);
// }

char	**fill_env_array(t_env *current, char **res)
{
	int		i;
	char	*tmp;

	i = 0;
	while (current)
	{
		tmp = ft_strjoin(current->var_name, "=");
		if (!tmp)
			return (free_array(res), NULL);
		if (current->value)
		{
			res[i] = ft_strjoin(tmp, current->value);
			free(tmp);
			if (!res[i])
				return (free_array(res), NULL);
		}
		i++;
		current = current->next;
	}
	res[i] = NULL;
	return (res);
}

char	**init_env_array(t_env *env_head)
{
	t_env	*current;
	char	**res;

	current = env_head;
	res = malloc(sizeof(char *) * (list_len(current) + 1));
	if (!res)
		return (NULL);
	return (fill_env_array(current, res));
}
