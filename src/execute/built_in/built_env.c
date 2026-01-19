/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:12:19 by almorene          #+#    #+#             */
/*   Updated: 2025/11/25 20:16:08 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_line *line)
{
	int	i;

	if (!line->g_environ)
		return (0);
	i = 0;
	while (line->g_environ[i])
	{
		if (ft_strchr(line->g_environ[i], '='))
			printf("%s\n", line->g_environ[i]);
		i++;
	}
	return (0);
}
