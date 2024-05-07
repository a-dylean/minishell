/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:38:03 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/07 16:29:23 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_for_export(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		return (EXIT_FAILURE);
	}
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (!ft_strchr(str, '='))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_export(t_shell *shell)
{
	if (!valid_for_export(shell->commands->cmd_name[1]))
		add_back_env_var(shell->env_head,
			init_env_node(shell->commands->cmd_name[1]));
	return (EXIT_SUCCESS);
}