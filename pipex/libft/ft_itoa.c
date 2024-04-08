/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:55:22 by jlabonde          #+#    #+#             */
/*   Updated: 2023/11/15 14:55:23 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_len_nb(int n)
{
	long int	len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len = 1;
	}
	if (n == 0)
		len = 1;
	else
	{
		while (n)
		{
			n = n / 10;
			len++;
		}
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*res;
	size_t		len;
	long int	nb;

	nb = (long int) n;
	len = ft_len_nb(nb);
	res = (char *) malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		res[0] = '0';
	res[len] = '\0';
	while (nb && len > 0)
	{
		res[len - 1] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	return (res);
}
