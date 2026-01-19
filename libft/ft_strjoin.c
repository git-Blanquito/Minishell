/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:54:06 by aiblanco          #+#    #+#             */
/*   Updated: 2022/09/28 16:54:09 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	pointerlen;
	char	*pointer;

	pointerlen = ft_strlen(s1) + ft_strlen(s2) + 1;
	pointer = ft_calloc(pointerlen, 1);
	if (!pointer)
		return (0);
	i = 0;
	j = 0;
	while (i < ft_strlen(s1) && ft_strlen(s1) != 0)
	{
		pointer[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2) && ft_strlen(s2) != 0)
	{
		pointer[i + j] = s2[j];
		j++;
	}
	pointer[i + j] = 0;
	return (pointer);
}
