/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:28:33 by almorene          #+#    #+#             */
/*   Updated: 2025/11/25 20:57:00 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	*create_heredoc(const char *delim, int index,
			int expand_vars, t_line *line)
{
	char	*filename;
	pid_t	pid;
	int		status;

	filename = gen_heredoc_filename(index);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), free(filename), NULL);
	if (pid == 0)
		child_heredoc(filename, delim, expand_vars, line);
	else
	{
		setup_signals_parent();
		waitpid(pid, &status, 0);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		unlink(filename);
		free(filename);
		return (NULL);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		unlink(filename);
		free(filename);
		return (NULL);
	}
	return (filename);
}*/

char	*create_heredoc(const char *delim, int index,
			int expand_vars, t_line *line)
{
	char	*filename;
	pid_t	pid;
	int		status;

	filename = gen_heredoc_filename(index);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), free(filename), NULL);
	if (pid == 0)
		child_heredoc(filename, delim, expand_vars, line);
	setup_signals_parent();
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		unlink(filename);
		return (free(filename), NULL);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (unlink(filename), free(filename), NULL);
	return (filename);
}

void	replace_dollar_status(t_args **argv, int last_status)
{
	char	*tmp;
	int		i;

	i = 0;
	while (argv && argv[i])
	{
		if (ft_strcmp(argv[i]->value, "$?") == 0)
		{
			tmp = ft_itoa(last_status);
			if (!tmp)
				handle_malloc_error(NULL, NULL, NULL, NULL);
			free(argv[i]->value);
			argv[i]->value = tmp;
		}
		i++;
	}
}

int	open_and_dup(const char *file, int flags, int mode, int dest_fd)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd < 0)
		return (perror("open"), -1);
	if (dup2(fd, dest_fd) == -1)
	{
		close(fd);
		return (perror("dup2"), -1);
	}
	close(fd);
	return (0);
}

int	apply_redirections(t_redir *rlist)
{
	while (rlist)
	{
		if (rlist->type == TOKEN_REDIR_IN)
		{
			if (open_and_dup(rlist->filename, O_RDONLY, 0, STDIN_FILENO) < 0)
				return (-1);
		}
		else if (rlist->type == TOKEN_REDIR_OUT)
		{
			if (open_and_dup(rlist->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644, STDOUT_FILENO) < 0)
				return (-1);
		}
		else if (rlist->type == TOKEN_APPEND)
		{
			if (open_and_dup(rlist->filename,
					O_WRONLY | O_CREAT | O_APPEND, 0644, STDOUT_FILENO) < 0)
				return (-1);
		}
		rlist = rlist->next;
	}
	return (0);
}

void	child_setup_io(t_cmd *cmd, int in_fd, int *fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	if (apply_redirections(cmd->redirs) < 0)
		exit(1);
}
