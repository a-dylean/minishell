/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:20:58 by jlabonde          #+#    #+#             */
/*   Updated: 2023/11/08 10:21:00 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	j;
	size_t	i;

	j = ft_strlen(dst);
	i = 0;
	while (src[i] && i + j + 1 < size)
	{
		dst[i + j] = src[i];
		i++;
	}
	if (i < size)
		dst[i + j] = '\0';
	if (size <= j)
		return (ft_strlen(src) + size);
	else
		return (ft_strlen(src) + j);
}
