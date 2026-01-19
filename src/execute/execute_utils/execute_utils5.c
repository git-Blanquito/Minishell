/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/10/23 00:28:15 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**args_to_argv(t_args **args)
{
	int		count;
	char	**res;
	int		i;

	if (!args || !args[0])
		return (NULL);
	count = 0;
	while (args[count])
		count++;
	res = ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (i < count)
	{
		res[i] = ft_strdup(args[i]->value);
		i++;
	}
	res[count] = NULL;
	return (res);
}

int	is_assignment(const char *s)
{
	const char	*eq;
	const char	*p;

	if (!s || !*s)
		return (0);
	eq = strchr(s, '=');
	if (!eq)
		return (0);
	if (eq == s)
		return (0);
	p = s;
	while (p < eq)
	{
		if (!ft_isalnum(*p) && *p != '_')
			return (0);
		p++;
	}
	return (1);
}
