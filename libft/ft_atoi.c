/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:35:25 by aiblanco          #+#    #+#             */
/*   Updated: 2022/12/29 20:20:24 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	retur(int *i)
{
	if (i[3] == 1)
		return (i[2] * (-1));
	return (i[2]);
}

int	ft_atoi(const char *str)
{
	int	i[5];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	i[4] = 0;
	while (str[i[0]])
	{
		if ((ft_isspace(str[i[0]]) == 1) && i[1] == 0 && i[4] == 0)
			i[0]++;
		else if ((str[i[0]] == '-' || str[i[0]] == '+') && i[4] == 0)
		{
			if (str[i[0]] == '-')
				i[3] = 1;
			i[0]++;
			i[1]++;
		}
		else if (str[i[0]] >= '0' && str[i[0]] <= '9' && i[1] <= 1
			&& i[4]++ >= 0)
			i[2] = (i[2] * 10) + (str[i[0]++] - '0');
		else
			return (retur(i));
	}
	return (retur(i));
}

/* int main(void)
{
	char *str =" 02-25";
	int	i;

	i = atoi(str);
	printf("%i\n",i);

	i = ft_atoi(str);
	printf("%i\n",i);
	return(0);
} */