/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:01:23 by almorene          #+#    #+#             */
/*   Updated: 2025/11/25 20:16:30 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_count(t_line *line)
{
	int	count;

	count = 0;
	while (line->g_environ && line->g_environ[count])
		count++;
	return (count);
}

static int	update_existing_env2(t_line *line, int idx, char *full_entry)
{
	free(line->g_environ[idx]);
	line->g_environ[idx] = full_entry;
	return (0);
}

static int	add_new_env(t_line *line, char *full_entry)
{
	int		n;
	int		j;
	char	**new_env;

	n = env_count(line);
	new_env = malloc(sizeof(char *) * (n + 2));
	if (!new_env)
		return (perror("malloc"), 1);
	j = -1;
	while (++j < n)
		new_env[j] = line->g_environ[j];
	new_env[n] = full_entry;
	new_env[n + 1] = NULL;
	free(line->g_environ);
	line->g_environ = new_env;
	return (0);
}

int	export_set_env(char *name, char *full_entry, t_line *line)
{
	int	idx;

	idx = env_index(name, line);
	if (idx >= 0)
		return (update_existing_env2(line, idx, full_entry));
	return (add_new_env(line, full_entry));
}
