/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:56:02 by almorene          #+#    #+#             */
/*   Updated: 2025/11/25 20:20:06 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value5(const char *name, t_line *line)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (line->g_environ[i])
	{
		if (!ft_strncmp(line->g_environ[i], name, len)
			&& line->g_environ[i][len] == '=')
			return (line->g_environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*get_env_value6(const char *name, char **envp)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	builtin_pwd(t_line *line)
{
	char	cwd[1024];
	char	*pwd;

	pwd = get_env_value5("PWD", line);
	if (pwd && *pwd)
	{
		printf("%s\n", pwd);
		return (0);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("minishell: pwd");
	return (1);
}
