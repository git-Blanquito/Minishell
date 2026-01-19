/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 19:01:23 by almorene          #+#    #+#             */
/*   Updated: 2025/11/25 20:16:45 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	names_match(char *a, char *b)
{
	size_t	i;

	if (ft_strlen(a) != ft_strlen(b))
		return (0);
	i = 0;
	while (a[i])
	{
		if (a[i] != b[i])
			return (0);
		i++;
	}
	return (1);
}

t_local_var	*find_local_var(char *name, t_local_var *vars)
{
	while (vars)
	{
		if (names_match(name, vars->name))
			return (vars);
		vars = vars->next;
	}
	return (NULL);
}

char	*looking_in_local_vars(char *name, t_line *line)
{
	t_local_var	*found;

	if (!line || !name)
		return (NULL);
	found = find_local_var(name, line->local_vars);
	if (found)
		return (found->value);
	return (NULL);
}

int	env_index(char *name, t_line *line)
{
	int		i;
	size_t	len;

	if (!line->g_environ)
		return (-1);
	i = 0;
	len = ft_strlen(name);
	while (line->g_environ[i])
	{
		if (strncmp(line->g_environ[i], name, len) == 0
			&& (line->g_environ[i][len] == '='
			|| line->g_environ[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}
