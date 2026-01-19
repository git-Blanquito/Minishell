/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:25:43 by aiblanco          #+#    #+#             */
/*   Updated: 2022/09/23 21:15:39 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	register unsigned char	u1;
	register unsigned char	u2;

	while (n > 0)
	{
		u1 = *s1;
		u2 = *s2;
		if (u1 != u2)
			return (u1 - u2);
		if (*s1 == 0)
			return (0);
		n--;
		s1++;
		s2++;
	}
	return (0);
}
