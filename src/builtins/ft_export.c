/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:38:03 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/07 14:58:05 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int valid_for_export(char *str)
{
	int i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		return (EXIT_FAILURE);
	}
	i++;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int ft_export(char *str, t_shell *shell)
{
	(void)str;
	(void)shell;
	// if (valid_for_export(str))
	// 	add_token_back(&shell->env_head, create);
	return (EXIT_SUCCESS);
}