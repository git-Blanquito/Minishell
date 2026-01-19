/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunnum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:21:47 by aiblanco          #+#    #+#             */
/*   Updated: 2023/01/14 23:21:53 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	untourstr(char *pointer, long int z, long int k)
{
	long int	n;

	n = z;
	if (n < 0)
	{
		pointer[0] = 45;
		n = n * (-1);
	}
	if (n == 0)
		pointer[--k] = 48;
	while (n > 0)
	{
		pointer[--k] = 48 + (n % 10);
		n = n / 10;
	}
}

static int	unlength(unsigned int z)
{
	unsigned long int	n;
	long int			i;

	n = z;
	i = 0;
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_unitoa(unsigned int z)
{
	char				*pointer;
	long int			k;
	unsigned long int	n;

	n = z;
	k = unlength(n);
	pointer = ft_calloc(k + 1, 1);
	if (!pointer)
		return (0);
	untourstr(pointer, n, k);
	return (pointer);
}

void	ft_printunnum(unsigned int num, int *pcharcount)
{
	char	*str;

	str = ft_unitoa(num);
	ft_printstr(str, pcharcount);
	free(str);
}
