/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:34:25 by aiblanco          #+#    #+#             */
/*   Updated: 2023/01/14 23:34:28 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr(char *str, int *pcharcount)
{
	if (str == NULL)
	{
		write(1, "(null)", 6);
		*pcharcount = (*pcharcount) + 6;
		return (0);
	}
	while (*str != 0)
	{
		write(1, str, 1);
		str++;
		(*pcharcount)++;
	}
	return (0);
}
