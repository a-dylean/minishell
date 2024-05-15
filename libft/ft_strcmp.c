/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <jlabonde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:26:35 by jlabonde          #+#    #+#             */
/*   Updated: 2024/05/15 17:40:35 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp(const char *s1, const char *s2)
{
	printf("s1: %s\n", s1);
	printf("s2: %s\n", s2);
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (*(const unsigned char*)s1 - *(const unsigned char*)s2);
}