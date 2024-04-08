/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:37:43 by jlabonde          #+#    #+#             */
/*   Updated: 2023/11/08 16:37:44 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	key;

	key = (char) c;
	while (*s)
	{
		if (*s == key)
			return ((char *)s);
		s++;
	}
	if (key == '\0')
		return ((char *)s);
	return (NULL);
}
