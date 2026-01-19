/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:35:32 by almorene          #+#    #+#             */
/*   Updated: 2025/10/13 21:35:51 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_n_option(char **argv, int *start_index)
{
	int	i;
	int	j;
	int	newline;

	newline = 1;
	i = 1;
	while (argv[i] && !ft_strncmp(argv[i], "-n", 2))
	{
		j = 2;
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0')
			break ;
		newline = 0;
		i++;
	}
	*start_index = i;
	return (newline);
}

static void	print_echo_args(char **argv, int i)
{
	while (argv[i])
	{
		if (argv[i][0] != '\0')
			printf("%s", argv[i]);
		if (argv[i + 1] && argv[i + 1][0] != '\0'
			&& argv[i + 1][0] != '"' && argv[i + 1][0] != '\'')
			printf(" ");
		i++;
	}
}

int	builtin_echo(char **argv)
{
	int	i;
	int	newline;

	newline = handle_n_option(argv, &i);
	print_echo_args(argv, i);
	if (newline)
		printf("\n");
	return (0);
}
