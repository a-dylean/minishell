/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:38:03 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/07 18:56:22 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_valid_identifier(char *str) 
{
    int i;
	if (!ft_isalpha(str[0]) && str[0] != '_')
        return 0;
    i = 1;
    while (str[i]) 
	{
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return 0;
        i++;
    }
    return (1);
}

int	valid_for_export(char *str)
{
    int	i;
    char **split;
    
	if (ft_strcmp(str, "=") == 0)
	{
        write_error("export" , "not a valid identifier");
        return (1);
    }
    split = ft_split(str, '=');
    if (!is_valid_identifier(split[0]))
    {
        write_error("export" , "not a valid identifier");
        return (1);
    }
    if (!split[1])
        return (0);
    i = 0;
    while (split[1][i])
    {
        if (!ft_isprint(split[1][i]))
            return (1);
        i++;
    }
	free_array(split);
    return (0);
}


void handle_export(char *str, t_shell *shell)
{
	t_env *tmp;
	char **split;
	
	split = ft_split(str, '=');
	tmp = shell->env_head;
	if (!env_var_exists(split[0], shell))
		add_back_env_var(shell->env_head, init_env_node(str));
	else
	{
		while(tmp)
		{
			if (ft_strcmp(tmp->var_name, split[0]) == 0)
			{
				free(tmp->value);
				tmp->value = get_env_value(str, split[0]);
				break;
			}
			tmp = tmp->next;
		}
	}
	free_array(split);
}

int	ft_export(char **cmd, t_shell *shell)
{
    int i;
    int exit_code;

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
        i++;
    }
    return (0);
}