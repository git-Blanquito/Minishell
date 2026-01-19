/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishelll                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco almorene <marvin@42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/07/22 02:41:03 by aial             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t j)
{
	size_t	i;
	char	*point;
	char	*point2;

	i = ft_strlen(s1);
	if (j > i)
		j = i;
	point = (char *)ft_calloc(j + 1, 1);
	if (!point)
		return (0);
	point2 = point;
	while (*s1 != 0 && j > 0)
	{
		*point = *s1;
		s1++;
		point++;
		j--;
	}
	return (point2);
}
/* int main ()
{
	char *str = "hala";
	char *str2;

	str2 = ft_strndup(str, 5);
	ft_printf("%s\n", str2);
	free(str2);
	str2 = strndup(str, 5);
	ft_printf("%s\n", str2);
	free(str2);
	return (0);
} */
