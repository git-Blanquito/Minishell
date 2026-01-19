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

int	exec_shell_builtin_with_redirs(
	t_cmd *cmd, int last_status, t_line *line)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	saved_stdin = -1;
	saved_stdout = -1;
	if (cmd->redirs)
	{
		if (save_stdio(&saved_stdin, &saved_stdout))
			return (1);
		if (apply_redirections(cmd->redirs) < 0)
			return (restore_stdio(saved_stdin, saved_stdout));
	}
	ret = exec_builtin(cmd, last_status, line);
	if (cmd->redirs)
		restore_stdio(saved_stdin, saved_stdout);
	return (ret);
}

int	exec_builtin(t_cmd *cmd, int last_status, t_line *line)
{
	char	**argv_c;
	int		ret;

	argv_c = args_to_argv(cmd->argv);
	if (!argv_c)
		return (1);
	if (!ft_strcmp(argv_c[0], "cd"))
		ret = builtin_cd(argv_c, line);
	else if (!ft_strcmp(argv_c[0], "echo"))
		ret = builtin_echo(argv_c);
	else if (!ft_strcmp(argv_c[0], "pwd"))
		ret = builtin_pwd(line);
	else if (!ft_strcmp(argv_c[0], "export"))
		ret = builtin_export(argv_c, line);
	else if (!ft_strcmp(argv_c[0], "unset"))
		ret = builtin_unset(argv_c, line);
	else if (!ft_strcmp(argv_c[0], "exit"))
		ret = builtin_exit(argv_c, last_status);
	else if (!ft_strcmp(argv_c[0], "env"))
		ret = builtin_env(line);
	else
		ret = 1;
	free_argv2(argv_c);
	return (ret);
}

char	*get_path_from_env(t_line *line)
{
	int	i;

	i = 0;
	if (!line->g_environ)
		return (NULL);
	while ((line->g_environ)[i])
	{
		if (ft_strncmp((line->g_environ)[i], "PATH=", 5) == 0)
			return ((line->g_environ)[i] + 5);
		i++;
	}
	return (NULL);
}

char	*search_in_dirs(char **dirs, char *cmd)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, F_OK) == 0)
		{
			free_argv2(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_argv2(dirs);
	return (NULL);
}

char	*find_executable(char *cmd, t_line *line)
{
	char	*path_env;
	char	**dirs;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_path_from_env(line);
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	return (search_in_dirs(dirs, cmd));
}
