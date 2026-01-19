/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <startarvin@42.fr:>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 19:37:06 by aiblanco          #+#    #+#             */
/*   Updated: 2022/09/27 19:37:11 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*string(const char *src, unsigned int start, size_t len)
{
	char	*pointer;

	if (ft_strlen(src) < len)
		len = ft_strlen(src);
	if (ft_strlen(src) <= start)
		return (ft_calloc(1, 1));
	if (ft_strlen(src) - (size_t)start > 0)
	{
		if (ft_strlen(src) - (size_t)start <= len)
			pointer = ft_calloc(ft_strlen(src) - (size_t)start + 1, 1);
		else
			pointer = ft_calloc(len + 1, 1);
	}
	else
		pointer = NULL;
	return (pointer);
}

char	*ft_substr(const char *src, unsigned int start, size_t len)
{
	char	*pointer;
	size_t	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	pointer = string(src, start, len);
	if (!pointer)
		return (NULL);
	while (src[i[0]] != 0)
	{
		if (i[0] >= start && (i[0] <= ((size_t)start - 1) + len) && start == 0
			&& len != 0)
			pointer[i[2]++] = src[i[0]];
		else if (i[0] >= start && i[0] < ((size_t)start + len))
		{
			pointer[i[2]] = src[i[0]];
			i[2]++;
		}
		i[0]++;
	}
	pointer[i[2]] = '\0';
	return (pointer);
}

/* int	main(void)
{
	char	a[] = "hola";
	size_t	b = 0;
	size_t	c = 1;
	char	*p;
	unsigned int start;
	start = 0;

	start = start - c;
	p = ft_substr(a, b, c);
	printf("%s\n", p);
	printf("%i", start);
	return (0);
} */