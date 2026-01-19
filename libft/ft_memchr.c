/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:59:47 by aiblanco          #+#    #+#             */
/*   Updated: 2022/09/24 19:28:20 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, int n)
{
	char	*point;
	char	k;

	point = (char *)s;
	k = (char)c;
	while (n-- > 0)
	{
		if (*point == k)
			return (point);
		point++;
	}
	return (0);
}
