/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/10/23 00:28:15 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_parent(pid_t pid)
{
	int	status;

	setup_signals_parent();
	waitpid(pid, &status, 0);
	handle_child_signal(status);
	return (get_exit_status_from_wait(status));
}

int	exec_external(t_cmd *cmd, t_line *line)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		exec_child_process(cmd, line);
		exit(1);
	}
	return (handle_parent(pid));
}

int	handle_assignment_if_needed(t_cmd *cmd, t_line *line, int i)
{
	char	*cmd_name;
	char	*eq;

	cmd_name = cmd->argv[i]->value;
	if (is_assignment(cmd_name) && cmd->argv[i + 1] == NULL)
	{
		eq = ft_strchr(cmd_name, '=');
		*eq = '\0';
		set_local_var(line, cmd_name, eq + 1);
		*eq = '=';
		return (1);
	}
	return (0);
}

int	exec_builtin_dispatch(t_cmd *cmd, int last_status, t_line *line, int i)
{
	t_args	**old_argv;
	int		ret;

	if (is_shell_builtin(cmd->argv[i]->value))
		return (exec_shell_builtin_with_redirs(cmd, last_status, line));
	old_argv = cmd->argv;
	cmd->argv = &cmd->argv[i];
	ret = exec_builtin_in_child(cmd, last_status, line);
	cmd->argv = old_argv;
	return (ret);
}

int	exec_external_dispatch(t_cmd *cmd, int i, t_line *line)
{
	t_args	**old_argv;
	int		ret;

	old_argv = cmd->argv;
	cmd->argv = &cmd->argv[i];
	ret = exec_external(cmd, line);
	cmd->argv = old_argv;
	return (ret);
}
