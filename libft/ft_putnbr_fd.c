/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:35:25 by aiblanco          #+#    #+#             */
/*   Updated: 2022/10/29 19:35:27 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			ft_putstr_fd("-", fd);
			n = n * (-1);
		}
		if (n > 9)
		{
			ft_putnbr_fd((n / 10), fd);
			n = (n % 10) + '0';
			ft_putchar_fd(n, fd);
		}
		if (n <= 9)
		{
			n = n + '0';
			ft_putchar_fd(n, fd);
		}
	}
}
