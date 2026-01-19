/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/10/30 15:24:11 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error(const char *s1, const char *s2, const char *s3)
{
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2)
		write(2, s2, ft_strlen(s2));
	if (s3)
		write(2, s3, ft_strlen(s3));
}

int	is_directory(const char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (1);
	}
	return (0);
}

void	handle_execve_error(char **argv_c, char *path)
{
	if (access(path, F_OK) != 0)
	{
		write_error("minishell: ", argv_c[0],
			": No such file or directory\n");
		free_argv3(argv_c, path);
		exit(127);
	}
	else if (is_directory(path))
	{
		write_error("minishell: ", argv_c[0], ": is a directory\n");
		free_argv3(argv_c, path);
		exit(126);
	}
	else if (access(path, X_OK) != 0)
	{
		write_error("minishell: ", argv_c[0], ": Permission denied\n");
		free_argv3(argv_c, path);
		exit(126);
	}
	perror("execve");
	free_argv3(argv_c, path);
	exit(126);
}

void	exec_child_process(t_cmd *cmd, t_line *line)
{
	char	**argv_c;
	char	*path;

	setup_signals_exec();
	if (apply_redirections(cmd->redirs) < 0)
		exit(1);
	argv_c = args_to_argv(cmd->argv);
	if (!argv_c)
		exit(1);
	path = find_executable(argv_c[0], line);
	if (!path)
	{
		write_error("minishell: ", argv_c[0], ": command not found\n");
		free_argv2(argv_c);
		exit(127);
	}
	disable_echoctl();
	execve(path, argv_c, line->g_environ);
	handle_execve_error(argv_c, path);
}

void	handle_child_signal(int status)
{
	if (!WIFSIGNALED(status))
		return ;
	if (WTERMSIG(status) == SIGINT)
		write(1, "^C\n", 3);
	else if (WTERMSIG(status) == SIGQUIT)
		write(1, "Quit (core dumped)\n", 19);
}
