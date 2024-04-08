/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:20:46 by jlabonde          #+#    #+#             */
/*   Updated: 2023/11/09 11:20:47 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*string;
	unsigned char		key;

	string = (unsigned char *) s;
	key = (unsigned char) c;
	while (n > 0)
	{
		if (*string == key)
			return ((void *) string);
		n--;
		string++;
	}
	if (n != 0)
		return ((void *) string);
	return (NULL);
}
