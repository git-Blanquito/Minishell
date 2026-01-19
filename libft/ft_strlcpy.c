/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:13:02 by aiblanco          #+#    #+#             */
/*   Updated: 2022/09/20 21:53:29 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* # include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h> */

// copies "dstsize" characters from one string to another.

int	ft_strlcpy(char *dst, const char *src, unsigned int dstsize)
{
	int	i;
	int	a;

	i = 0;
	if (dstsize != 0)
	{
		while ((src[i] != '\0') && (dstsize > 1))
		{
			if (dstsize > 1)
				dst[i] = src[i];
			i++;
			dstsize--;
		}
		if (src[i] == '\0' || dstsize == 1)
			dst[i] = '\0';
	}
	a = 0;
	while (*src != '\0')
	{
		src++;
		a++;
	}
	return (a);
}

/* int	main(void)
{
	char	dst[] = "hola";
	char	src[] = "aaa";
	int		j;

	j = ft_strlcpy(dst, src, 3);
	printf("%s\n",dst);
	return (0);
} */