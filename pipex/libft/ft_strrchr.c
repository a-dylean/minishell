/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:08:32 by jlabonde          #+#    #+#             */
/*   Updated: 2023/11/08 17:08:34 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	key;
	int				i;

	i = 0;
	key = (unsigned char) c;
	while (*s)
	{
		i++;
		s++;
	}
	while (i >= 0)
	{
		if (*s == key)
			return ((char *) s);
		else
		{
			i--;
			s--;
		}
	}
	return (0);
}
