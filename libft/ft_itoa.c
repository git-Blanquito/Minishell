/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 19:17:18 by aiblanco          #+#    #+#             */
/*   Updated: 2022/10/23 19:17:21 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	tourstr(char *pointer, long int z, long int k)
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

static int	length(int z)
{
	long int	n;
	long int	i;

	n = z;
	i = 0;
	if (n < 0)
	{
		n = n * (-1);
		i++;
	}
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int z)
{
	char		*pointer;
	long int	k;
	long int	n;

	n = z;
	k = length(n);
	pointer = ft_calloc(k + 1, 1);
	if (!pointer)
		return (0);
	tourstr(pointer, n, k);
	return (pointer);
}
