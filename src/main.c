/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/11/25 18:54:20 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_last_status;

static void	init_shell(t_line *line, int *last_status, char **envp)
{
	*last_status = 0;
	line->local_vars = NULL;
	if (init_env(envp, line))
		exit(1);
}

static void	process_input(t_line *line, char *input, int *last_status)
{
	if (is_only_white_space(input))
	{
		free(input);
		return ;
	}
	if (*input)
		line_comander(line, input, last_status);
	else
		free(input);
}

static void	main_loop(t_line *line, int *last_status)
{
	char	*input;

	while (1)
	{
		setup_signals_prompt();
		input = readline("~ ");
		if (!input)
			cleanup_and_exit(*last_status, line);
		process_input(line, input, last_status);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_line	line;

	g_last_status = 0;
	(void)argc;
	(void)argv;
	init_shell(&line, &g_last_status, envp);
	main_loop(&line, &g_last_status);
	free_argv2(line.g_environ);
	return (0);
}
