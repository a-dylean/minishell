/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atonkopi <atonkopi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:31:02 by atonkopi          #+#    #+#             */
/*   Updated: 2024/05/09 18:53:19 by atonkopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**init_array(int size)
{
	char	**array;

	array = malloc((size + 1) * sizeof(char *));
	if (!array)
		exit(EXIT_FAILURE);
	return (array);
}

void	free_array(char **arr)
{
	int i;

	if (arr)
	{
		i = 0;
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}