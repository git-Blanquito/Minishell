/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:56:02 by almorene          #+#    #+#             */
/*   Updated: 2025/11/25 20:20:24 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_env_var(char *name, t_line *line)
{
	int	n;
	int	j;
	int	idx;

	idx = env_index(name, line);
	if (idx < 0)
		return (0);
	n = env_count(line);
	free(line->g_environ[idx]);
	j = idx;
	while (j < n)
	{
		line->g_environ[j] = line->g_environ[j + 1];
		j++;
	}
	return (1);
}

static int	is_valid_name_unset(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_unset(char **args, t_line *line)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_name_unset(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			i++;
			continue ;
		}
		remove_env_var(args[i], line);
		i++;
	}
	return (0);
}
