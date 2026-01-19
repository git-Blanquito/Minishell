/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:40:42 by almorene          #+#    #+#             */
/*   Updated: 2025/10/23 18:50:11 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*itoa_status(int n)
{
	return (ft_itoa(n));
}

int	is_name_start(int c)
{
	return (isalpha(c) || c == '_');
}

int	is_name_char(int c)
{
	return (isalnum(c) || c == '_');
}

char	*xstrdup(const char *s)
{
	size_t	n;
	char	*r;

	if (!s)
		return (NULL);
	n = ft_strlen(s);
	r = malloc(n + 1);
	if (!r)
		return (NULL);
	ft_memcpy(r, s, n + 1);
	return (r);
}
