/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:23:50 by jlabonde          #+#    #+#             */
/*   Updated: 2023/11/10 12:23:51 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*ptr;

	if ((elementCount * elementSize) > 65535
		|| (elementSize > 65535 && elementCount > 65535))
		return (0);
	ptr = (void *) malloc(elementCount * elementSize);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (elementCount * elementSize));
	return (ptr);
}
