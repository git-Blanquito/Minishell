/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:28:33 by almorene          #+#    #+#             */
/*   Updated: 2025/10/10 14:28:41 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	execute_pipeline(t_cmd *cmds, t_line *line)
{
	t_pipe_ctx	ctx;
	pid_t		pid;
	int			status;

	ctx.in_fd = STDIN_FILENO;
	ctx.pid_count = 0;
	while (cmds)
	{
		pid = spawn_child(cmds, ctx.fd);
		if (pid == -1)
		{
			if (ctx.in_fd != STDIN_FILENO)
				close(ctx.in_fd);
			return (1);
		}
		if (pid == 0)
		{
			setup_signals_exec();
			child_setup_io(cmds, ctx.in_fd, ctx.fd);
			child_execute_cmd(cmds, 0, line);
		}
		else
		{
			setup_signals_parent();
			waitpid(pid, &status, 0);
		}
		parent_post_fork(&ctx, pid, cmds->next != NULL);
		cmds = cmds->next;
	}
	cleanup_pipeline_heredocs(line);
	return (wait_all_children(ctx.pids, ctx.pid_count));
}*/

static int	handle_pipeline_cmd(t_cmd *cmd, t_pipe_ctx *ctx, t_line *line)
{
	pid_t	pid;

	pid = spawn_child(cmd, ctx->fd);
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		setup_signals_exec();
		child_setup_io(cmd, ctx->in_fd, ctx->fd);
		child_execute_cmd(cmd, 0, line);
		exit(1);
	}
	setup_signals_parent();
	parent_post_fork(ctx, pid, cmd->next != NULL);
	return (0);
}

int	execute_pipeline(t_cmd *cmds, t_line *line)
{
	t_pipe_ctx	ctx;

	ctx.in_fd = STDIN_FILENO;
	ctx.pid_count = 0;
	while (cmds)
	{
		if (handle_pipeline_cmd(cmds, &ctx, line) < 0)
			return (1);
		cmds = cmds->next;
	}
	cleanup_pipeline_heredocs(line);
	return (wait_all_children(ctx.pids, ctx.pid_count));
}
