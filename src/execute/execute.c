/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/11/13 23:24:51 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_empty_command(t_cmd *cmd)
{
	int	save_in;
	int	save_out;
	int	ret;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	ret = apply_redirections(cmd->redirs);
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
	if (ret < 0)
		return (1);
	return (0);
}

static int	handle_no_argv(t_cmd *cmd)
{
	if (apply_redirections(cmd->redirs) < 0)
		return (1);
	if (cmd->argv && cmd->argv[0]
		&& (cmd->argv[0]->was_single_quoted || cmd->argv[0]->was_double_quoted))
	{
		ft_putstr_fd("minishell: : command not found\n", 2);
		return (127);
	}
	return (0);
}

static int	dispatch_command(t_cmd *cmd,
	int last_status, t_line *line, int i)
{
	char	*cmd_name;

	cmd_name = cmd->argv[i]->value;
	if (handle_assignment_if_needed(cmd, line, i))
		return (0);
	if (is_builtin(cmd_name))
		return (exec_builtin_dispatch(cmd, last_status, line, i));
	return (exec_external_dispatch(cmd, i, line));
}

int	execute_command(t_cmd *cmd, int last_status, t_line *line)
{
	int	i;

	if (!cmd)
		return (0);
	if (!cmd->argv || !cmd->argv[0])
		return (exec_empty_command(cmd));
	if (cmd->next)
		return (execute_pipeline(cmd, line));
	i = 0;
	while (cmd->argv[i] && cmd->argv[i]->value[0] == '\0')
		i++;
	if (!cmd->argv[i])
		return (handle_no_argv(cmd));
	return (dispatch_command(cmd, last_status, line, i));
}
