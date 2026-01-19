/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 19:48:55 by aiblanco          #+#    #+#             */
/*   Updated: 2022/09/21 18:06:46 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copy the first n characters of one string to another. */

void	*ft_memcpy(void *dst, const void *src, int n)
{
	int	k;

	k = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n-- > 0)
	{
		*(char *)dst = *(char *)src;
		dst++;
		src++;
		k++;
	}
	while (k-- > 0)
		dst--;
	return (dst);
}
