/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:55:27 by almorene          #+#    #+#             */
/*   Updated: 2025/11/25 20:15:40 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_env_entry(const char *name, const char *value)
{
	char	*entry;
	size_t	len_name;
	size_t	len_value;

	len_name = ft_strlen(name);
	len_value = ft_strlen(value);
	entry = malloc(len_name + len_value + 2);
	if (!entry)
		handle_malloc_error(NULL, NULL, NULL, NULL);
	ft_strlcpy(entry, name, len_name + 1);
	entry[len_name] = '=';
	ft_strlcpy(entry + len_name + 1, value, len_value + 1);
	return (entry);
}

void	update_existing_env(t_line *line, char *entry, int idx)
{
	free(line->g_environ[idx]);
	line->g_environ[idx] = entry;
}

void	add_new_env_entry(t_line *line, char *entry)
{
	int		i;
	char	**new_env;

	i = 0;
	while (line->g_environ[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		handle_malloc_error(NULL, NULL, NULL, NULL);
	i = 0;
	while (line->g_environ[i])
	{
		new_env[i] = line->g_environ[i];
		i++;
	}
	new_env[i] = entry;
	new_env[i + 1] = NULL;
	free(line->g_environ);
	line->g_environ = new_env;
}
