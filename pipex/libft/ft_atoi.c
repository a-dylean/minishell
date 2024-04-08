/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:44:36 by jlabonde          #+#    #+#             */
/*   Updated: 2023/11/10 11:44:38 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*nptr && ((*nptr >= 9 && *nptr <= 13) || *nptr == 32))
		nptr++;
	if (*nptr == 45)
	{
		sign = -sign;
		nptr++;
	}
	else if (*nptr == 43)
		nptr++;
	while (*nptr && ((*nptr >= '0' && *nptr <= '9')))
	{
		res = res * 10 + *nptr - '0';
		nptr++;
	}
	return (sign * res);
}
