/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:44:39 by aiblanco          #+#    #+#             */
/*   Updated: 2022/09/17 19:07:18 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Counts and returns the number of characters in the string.
size_t	ft_strlen(const char *s)
{
	size_t	a;

	a = 0;
	while (*s != '\0')
	{
		s++;
		a++;
	}
	return (a);
}
