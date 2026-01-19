/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:28:59 by aiblanco          #+#    #+#             */
/*   Updated: 2022/10/29 18:29:03 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*pointer;
	int		i;
	int		z;

	z = 0;
	i = ft_strlen(s);
	pointer = ft_calloc(i + 1, 1);
	if (!pointer)
		return (0);
	while (z < i)
	{
		pointer[z] = f(z, s[z]);
		z++;
	}
	return (pointer);
}
