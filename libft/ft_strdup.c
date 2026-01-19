/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:15:33 by aiblanco          #+#    #+#             */
/*   Updated: 2022/09/26 22:16:03 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*point;
	char	*point2;

	i = ft_strlen(s1);
	point = (char *)ft_calloc(i + 1, 1);
	if (!point)
		return (0);
	point2 = point;
	while (*s1 != 0)
	{
		*point = *s1;
		s1++;
		point++;
	}
	*point = *s1;
	return (point2);
}
