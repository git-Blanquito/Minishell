/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:55:27 by almorene          #+#    #+#             */
/*   Updated: 2025/11/25 20:14:03 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_index2(const char *name, t_line *line)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (line->g_environ && line->g_environ[i])
	{
		if (!ft_strncmp(line->g_environ[i], name, len)
			&& line->g_environ[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env_value2(const char *name, t_line *line)
{
	int		idx;
	size_t	len;

	len = ft_strlen(name);
	idx = env_index2(name, line);
	if (idx == -1)
		return (NULL);
	return (line->g_environ[idx] + len + 1);
}

void	update_env_var(const char *name, const char *value, t_line *line)
{
	int		idx;
	char	*entry;

	entry = create_env_entry(name, value);
	if (!entry)
		handle_malloc_error(NULL, NULL, NULL, NULL);
	idx = env_index2(name, line);
	if (idx >= 0)
		update_existing_env(line, entry, idx);
	else
		add_new_env_entry(line, entry);
}

int	cd_error(const char *msg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
