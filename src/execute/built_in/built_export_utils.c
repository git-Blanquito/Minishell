/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:01:23 by almorene          #+#    #+#             */
/*   Updated: 2025/11/25 20:17:05 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_name(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!(isalpha(*name) || *name == '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!(isalnum(name[i]) || name[i] == '_' || name[i] == '='))
			return (0);
		i++;
	}
	return (1);
}

void	sort_env(char **arr, int n)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	copy_environ_to_copy(char **copy, t_line *line, int n)
{
	int	j;

	j = 0;
	while (j < n)
	{
		copy[j] = line->g_environ[j];
		j++;
	}
	copy[n] = NULL;
}

static void	print_sorted_env(char **copy, int n)
{
	int		j;
	char	*eq;

	j = 0;
	while (j < n)
	{
		eq = ft_strchr(copy[j], '=');
		if (eq)
			printf("declare -x %.*s=\"%s\"\n", (int)(eq - copy[j]),
				copy[j], eq + 1);
		else
			printf("declare -x %s\n", copy[j]);
		j++;
	}
}

int	export_print_env(t_line *line)
{
	int		n;
	char	**copy;

	n = env_count(line);
	copy = malloc(sizeof(char *) * (n + 1));
	if (!copy)
		return (perror("malloc"), 1);
	copy_environ_to_copy(copy, line, n);
	sort_env(copy, n);
	print_sorted_env(copy, n);
	free(copy);
	return (0);
}
