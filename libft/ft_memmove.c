/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 20:34:31 by aiblanco          #+#    #+#             */
/*   Updated: 2022/09/21 01:58:55 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copies a part of the string to another position in the same or another 
string.
    To avoid overlapping, exit the second part of the if, 
writing from back to front of the string.
    Return the original destination pointer. */

void	*ft_memmove(void *dst, const void *src, int len)
{
	char	*punt;

	if (dst == NULL && src == NULL)
		return (NULL);
	punt = dst;
	if ((char *)punt < (char *)src)
	{
		while (len-- > 0)
		{
			*(char *)punt = *(char *)src;
			punt++;
			src++;
		}
	}
	else
	{
		while (len-- > 0)
			*((char *)dst + len) = *((char *)src + len);
	}
	return (dst);
}
