/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:32:41 by aiblanco          #+#    #+#             */
/*   Updated: 2022/09/26 20:38:54 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*point;

	if (count == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	point = malloc(count * size);
	if (!point)
		return (NULL);
	return (ft_memset(point, 0,
			(count * size)));
}
