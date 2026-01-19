/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/11/22 20:16:51 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_env_values(char **envp, int count, t_line *line)
{
	int	i;

	i = 0;
	while (i < count)
	{
		line->g_environ[i] = ft_strdup(envp[i]);
		if (!line->g_environ[i])
		{
			free_argv2(line->g_environ);
			line->g_environ = NULL;
			return (1);
		}
		i++;
	}
	line->g_environ[i] = NULL;
	return (0);
}

int	dup_env(char **envp, t_line *line)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	line->g_environ = malloc(sizeof(char *) * (count + 1));
	if (!line->g_environ)
		return (1);
	if (copy_env_values(envp, count, line))
	{
		line->g_environ = NULL;
		return (1);
	}
	return (0);
}
