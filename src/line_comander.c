/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_comander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/11/09 21:09:52 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_cmd_errors(t_line *line, char *input)
{
	free_token(line->tokens);
	free_commands(line->cmds);
	free(input);
	line->tokens = NULL;
	line->cmds = NULL;
	return (1);
}

static int	check_cmd_errors(t_line *line, char *input)
{
	t_cmd	*cmd;

	cmd = line->cmds;
	while (cmd)
	{
		if (cmd->error == 1)
			return (handle_cmd_errors(line, input));
		cmd = cmd->next;
	}
	return (0);
}

void	line_comander(t_line *line, char *input, int *last_status)
{
	t_cmd	*cmd;

	add_history(input);
	line->tokens = tokenize(input, *last_status, line);
	if (!line->tokens)
	{
		print_exit_error("Error: of \" , \' or malloc\n");
		free(input);
		return ;
	}
	line->cmds = parse_tokens(line->tokens);
	if (!line->cmds)
		return ((void)handle_cmd_errors(line, input));
	if (check_cmd_errors(line, input))
		return ;
	cmd = line->cmds;
	if (cmd)
		g_last_status = execute_command(cmd, *last_status, line);
	*last_status = g_last_status;
	free_main_mem(line->tokens, line->cmds, input);
}
