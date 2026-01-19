/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:35:32 by almorene          #+#    #+#             */
/*   Updated: 2025/10/13 21:35:51 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd_home(t_line *line)
{
	char	*home;

	home = get_env_value5("HOME", line);
	if (!home)
		return (cd_error("HOME not set"), NULL);
	return (home);
}

static char	*cd_oldpwd(t_line *line)
{
	char	*old;

	old = get_env_value5("OLDPWD", line);
	if (!old)
		return (cd_error("OLDPWD not set"), NULL);
	printf("%s\n", old);
	return (old);
}

char	*get_cd_target(char **args, char *oldpwd, t_line *line)
{
	if (!getcwd(oldpwd, 4096))
		return (cd_error("getcwd failed"), NULL);
	if (!args[1] || !ft_strcmp(args[1], "~"))
		return (cd_home(line));
	if (!ft_strcmp(args[1], "-"))
		return (cd_oldpwd(line));
	if (args[1][0] == '\0')
		return (cd_home(line));
	return (args[1]);
}

int	change_directory(char *target, char *oldpwd, t_line *line)
{
	char	cwd[4096];

	if (chdir(target) != 0)
		return (perror("minishell: cd"), 1);
	if (!getcwd(cwd, sizeof(cwd)))
		return (perror("minishell: cd"), 1);
	update_env_var("OLDPWD", oldpwd, line);
	update_env_var("PWD", cwd, line);
	return (0);
}

int	builtin_cd(char **args, t_line *line)
{
	char	oldpwd[4096];
	char	*target;
	int		arg_count;

	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	if (arg_count > 2)
		return (cd_error("too many arguments"));
	target = get_cd_target(args, oldpwd, line);
	if (!target)
		return (1);
	return (change_directory(target, oldpwd, line));
}
