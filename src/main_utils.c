/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/10/30 15:20:56 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_and_exit(int last_status, t_line *line)
{
	printf("exit\n");
	rl_clear_history();
	free_argv2(line->g_environ);
	exit(last_status);
}

int	init_env(char **envp, t_line *line)
{
	if (dup_env(envp, line))
	{
		if (line->g_environ)
			free_argv2(line->g_environ);
		perror("Failed to duplicate environment");
		return (1);
	}
	return (0);
}

int	is_only_white_space(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
