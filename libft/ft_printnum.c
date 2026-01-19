/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:31:38 by aiblanco          #+#    #+#             */
/*   Updated: 2023/01/14 23:31:41 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printnum(int num, int *pcharcount)
{
	char	*str;

	str = ft_itoa(num);
	ft_printstr(str, pcharcount);
	free(str);
}
