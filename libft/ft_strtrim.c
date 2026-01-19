/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:22:17 by aiblanco          #+#    #+#             */
/*   Updated: 2022/10/02 17:22:19 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char const	*ft_end(char const *s, char const *set)
{
	int			j;
	int			k;
	char const	*pointer;

	k = 0;
	j = 0;
	while (s[j] != 0)
		j++;
	j--;
	while ((ft_strrchr(set, s[j]) != 0) && j > k)
		j--;
	pointer = &s[j];
	return (pointer);
}

static void	*callok(long int count, long int size)
{
	char	*pointer3;

	pointer3 = ft_calloc(count, size);
	if (!pointer3)
		return (0);
	return (pointer3);
}

static char const	*ft_start(char const *s, char const *set)
{
	int			i;
	int			j;
	char const	*pointer;

	j = 0;
	i = ft_strlen(s);
	pointer = &s[j];
	while ((ft_strchr(set, s[j]) != 0) && j < i)
		j++;
	pointer = &s[j];
	return (pointer);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char const	*pointer1;
	char const	*pointer2;
	int			i[2];
	char		*pointer3;

	i[0] = 0;
	i[1] = 0;
	if (s == 0)
		return ((char *)s);
	if (set == 0)
		return (ft_strdup(s));
	pointer1 = ft_start(s, set);
	pointer2 = ft_end(s, set);
	pointer2 = pointer2 + 1;
	if (pointer2 >= pointer1)
		i[1] = (pointer2 - pointer1) + 1;
	if (pointer1 > pointer2)
		return (callok(1, 1));
	pointer3 = ft_calloc(i[1], 1);
	if (!pointer3)
		return (0);
	while (pointer1 < pointer2)
		pointer3[i[0]++] = *pointer1++;
	return ((pointer3));
}
