/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 22:03:22 by aiblanco          #+#    #+#             */
/*   Updated: 2022/09/21 01:31:42 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Copies one string to another up to the maximum length of "dst".

int	ft_strlcat(char *dst, const char *src, unsigned int dstsize)
{
	unsigned int	j;
	unsigned int	k;
	int				i;

	i = 0;
	j = ft_strlen(dst);
	k = ft_strlen(src);
	if (dstsize <= j)
		return (k + dstsize);
	while (((j + i) < (dstsize - 1)) && (src[i] != 0))
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (j + k);
}
