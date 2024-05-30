/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:38:03 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/22 16:26:28 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_env_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isprint(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	valid_for_export(char *str)
{
	char	**split;

	if (ft_strlen(str) == 0)
		return (write_error("export", "not a valid identifier", str), 1);
	if (!ft_strchr(str, '=') || str[0] == '=')
	{
		if (!is_valid_identifier(str))
			return (write_error("export", "not a valid identifier", str), 1);
		return (-1);
	}
	split = ft_split(str, '=');
	if (ft_strcmp(str, "=") == 0 || !is_valid_identifier(split[0]))
	{
		if (split[0][0] == '-')
			return (write_error("export", "invalid option", split[0]),
				free_array(split), 2);
		return (write_error("export", "not a valid identifier", str),
			free_array(split), 1);
	}
	if (!split[1])
		return (free_array(split), 0);
	if (!is_valid_env_value(split[1]))
		return (free_array(split), 1);
	return (free_array(split), 0);
}

void	handle_export(char *str, t_shell *shell)
{
	t_env	*tmp;
	char	**split;

	split = ft_split(str, '=');
	tmp = shell->env_list;
	if (!var_exists(shell->env_list, split[0]))
		add_back_env_var(&shell->env_list, init_env_node(str));
	else
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->var_name, split[0]) == 0)
			{
				free(tmp->value);
				tmp->value = get_env_value(str, split[0]);
				break ;
			}
			tmp = tmp->next;
		}
	}
	free_array(split);
}

int	ft_export(char **cmd, t_shell *shell)
{
	int	i;
	int	exit_code;

	if (!cmd[1])
	{
		ft_env(shell);
		return (0);
	}
	i = 1;
	while (cmd[i])
	{
		exit_code = valid_for_export(cmd[i]);
		if (exit_code == 0)
			handle_export(cmd[i], shell);
		else if (exit_code == 1)
			return (1);
		else if (exit_code == 2)
			return (2);
		i++;
	}
	return (0);
}
