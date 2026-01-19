/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:21:12 by aiblanco          #+#    #+#             */
/*   Updated: 2023/01/14 23:21:18 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	maxprinthex(unsigned long long num)
{
	if (num > 9)
	{
		num = num - 10 + 'A';
		write(1, &num, 1);
	}
	else
	{
		num = num + '0';
		write(1, &num, 1);
	}
}

static void	maxninehex(unsigned long long num, int *pcharcount)
{
	if (num >= 16)
	{
		maxninehex(num / 16, pcharcount);
		maxprinthex(num % 16);
		(*pcharcount)++;
	}
	else
	{
		maxprinthex(num);
		(*pcharcount)++;
	}
}

void	ft_printhex(unsigned int num, int *pcharcount, char c)
{
	if (c == 'x')
		ninehex(num, pcharcount);
	else
		maxninehex(num, pcharcount);
}
