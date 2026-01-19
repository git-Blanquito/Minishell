/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_main_mem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/10/30 14:22:49 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_main_mem(t_token *head, t_cmd *cmds, char	*input)
{
	free_token(head);
	free_commands(cmds);
	free(input);
}

void	free_argv3(char **argv, char *str)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free((argv[i]));
		i++;
	}
	free(argv);
	if (str)
		free(str);
}
