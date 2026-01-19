/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:12:19 by almorene          #+#    #+#             */
/*   Updated: 2025/11/10 20:24:20 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric_argument(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_overflow(const char *str)
{
	int					sign;
	unsigned long long	result;
	int					i;

	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		result = result * 10 + (str[i] - '0');
		if ((sign == 1 && result > (unsigned long long)LLONG_MAX)
			|| (sign == -1 && result > (unsigned long long)LLONG_MAX + 1ULL))
			return (1);
		i++;
	}
	return (0);
}

int	builtin_exit(char **args, int last_status)
{
	long long	code;

	printf("exit\n");
	if (!args[1])
		exit(last_status);
	if (!is_numeric_argument(args[1]) || check_overflow(args[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 28);
		exit(2);
	}
	if (args[2] != NULL)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	code = ft_atol(args[1]);
	free_argv2(args);
	exit((unsigned char)code);
}
