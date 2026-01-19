/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:27:37 by aiblanco          #+#    #+#             */
/*   Updated: 2023/08/31 20:41:02 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	strleng_gnl(const char *str)
{
	size_t	count;

	count = 0;
	if (!str)
		return (0);
	while (*(str + count))
		count++;
	return (count);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[strleng_gnl(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i[2];
	char	*str;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	str = malloc(sizeof(char) * ((strleng_gnl(s1) + strleng_gnl(s2)) + 1));
	if (!str)
		return (freeft(s1));
	i[0] = -1;
	i[1] = 0;
	if (s1)
		while (s1[++i[0]])
			str[i[0]] = s1[i[0]];
	while (s2[i[1]])
		str[i[0]++] = s2[i[1]++];
	str[i[0]] = '\0';
	free(s1);
	return (str);
}
