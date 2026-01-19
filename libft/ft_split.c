/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:17:20 by aiblanco          #+#    #+#             */
/*   Updated: 2022/10/16 15:17:31 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countarrays(char const *s, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*s)
	{
		if (*s != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*s == c)
			trigger = 0;
		s++;
	}
	return (i);
}

static char	*word_dup(char const *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc(finish - start + 1, 1);
	if (!word)
		return (0);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = 0;
	return (word);
}

static char	**errormem(char **array)
{
	int	p;

	p = 0;
	while (array[p])
	{
		free(array[p]);
		p++;
	}
	free(array);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		index;
	int		j;
	size_t	i;

	i = -1;
	j = 0;
	index = -1;
	array = ft_calloc(countarrays(s, c) + 1, 8);
	if (!array || !s)
		return (0);
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			array[j++] = word_dup(s, index, i);
			if (!array[j - 1])
				return (errormem(array));
			index = -1;
		}
	}
	array[j] = NULL;
	return (array);
}
