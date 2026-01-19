/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ninehex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:33:49 by aiblanco          #+#    #+#             */
/*   Updated: 2023/01/14 23:33:52 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	printhex(unsigned long long num)
{
	if (num > 9)
	{
		num = num - 10 + 'a';
		write(1, &num, 1);
	}
	else
	{
		num = num + '0';
		write(1, &num, 1);
	}
}

void	ninehex(unsigned long long num, int *pcharcount)
{
	if (num >= 16)
	{
		ninehex(num / 16, pcharcount);
		printhex(num % 16);
		(*pcharcount)++;
	}
	else
	{
		printhex(num);
		(*pcharcount)++;
	}
}
