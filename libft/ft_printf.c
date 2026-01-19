/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:46:45 by aiblanco          #+#    #+#             */
/*   Updated: 2023/01/09 19:46:49 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	chooseformat(const char *str, int *pcharcount, va_list arg)
{
	if (*str == 'c')
		ft_printchar(va_arg(arg, int), pcharcount);
	else if (*str == 's')
		ft_printstr(va_arg(arg, char *), pcharcount);
	else if (*str == 'p')
		ft_printptr(va_arg(arg, unsigned long long), pcharcount);
	else if (*str == 'd' || *str == 'i')
		ft_printnum(va_arg(arg, int), pcharcount);
	else if (*str == 'u')
		ft_printunnum(va_arg(arg, unsigned int), pcharcount);
	else if (*str == 'x' || *str == 'X')
		ft_printhex(va_arg(arg, unsigned int), pcharcount, *str);
	else if (*str == '%')
	{
		write(1, "%", 1);
		(*pcharcount)++;
	}
}

int	ft_printf(char const *str, ...)
{
	va_list	arg;
	int		charcount;
	int		*pcharcount;

	charcount = 0;
	pcharcount = &charcount;
	va_start(arg, str);
	while (*str != 0)
	{
		if (*str == '%')
		{
			str++;
			chooseformat(str, pcharcount, arg);
		}
		else
		{
			write(1, str, 1);
			charcount++;
		}
		str++;
	}
	va_end(arg);
	return (charcount);
}

/* int	main(void)
{
	int	z;
	int	k;
	char *j;

	j = "achus jesus";
	z = -2147483648;
	k = printf("hola que %i la %s\n", j, z);
	printf("cuenta esto %i\n", k);

	k = ft_printf("hola que %i la\n", z);
	printf("cuenta esto %i string %s\n", k, j);
	return (0);
}  */
