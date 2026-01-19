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

void	child_execute_cmd(t_cmd *cmd,
						int last_status, t_line *line)
{
	char	*path;
	char	**argv;

	replace_dollar_status(cmd->argv, last_status >> 8);
	if (is_builtin(cmd->argv[0]->value))
		exit(exec_builtin(cmd, last_status >> 8, line));
	path = find_executable(cmd->argv[0]->value, line);
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd->argv[0]->value);
		exit(127);
	}
	argv = build_execve_argv(cmd->argv);
	execve(path, argv, line->g_environ);
	free_argv2(argv);
	perror("execve");
	exit(126);
}

pid_t	spawn_child(t_cmd *cmd, int *fd)
{
	pid_t	pid;

	if (cmd->next && pipe(fd) < 0)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	return (pid);
}

int	wait_all_children(pid_t *pids, int count)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		if (i == count - 1)
			last_status = get_exit_status_from_wait(status);
		i++;
	}
	return (last_status);
}

void	cleanup_pipeline_heredocs(t_line *line)
{
	t_cmd	*c;

	c = line->cmds;
	while (c)
	{
		cleanup_heredocs(c->redirs);
		c = c->next;
	}
}

void	parent_post_fork(t_pipe_ctx *ctx, pid_t pid, int has_next)
{
	ctx->pids[ctx->pid_count++] = pid;
	if (ctx->in_fd != STDIN_FILENO)
		close(ctx->in_fd);
	if (has_next)
	{
		close(ctx->fd[1]);
		ctx->in_fd = ctx->fd[0];
	}
}
