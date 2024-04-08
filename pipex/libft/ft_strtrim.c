/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlabonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:43:41 by jlabonde          #+#    #+#             */
/*   Updated: 2023/11/15 11:43:42 by jlabonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ischarset(char const s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*cpy;
	size_t	begin;
	size_t	end;
	int		i;

	i = 0;
	begin = 0;
	end = ft_strlen(s1);
	while (ft_ischarset (s1[begin], set))
		begin++;
	while (end > begin && ft_ischarset (s1[end - 1], set))
		end--;
	cpy = (char *) malloc((end - begin + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	while (begin < end)
	{
		cpy[i] = s1[begin];
		begin++;
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
