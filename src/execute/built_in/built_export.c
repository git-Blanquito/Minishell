/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 19:53:30 by almorene          #+#    #+#             */
/*   Updated: 2025/11/25 20:17:32 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*export_join(char *name, char *value, int has_equal)
{
	char	*res;
	size_t	len;

	len = ft_strlen(name);
	if (has_equal)
	{
		len += 1;
		if (value)
			len += ft_strlen(value);
	}
	res = malloc(len + 1);
	if (!res)
		return (perror("malloc"), NULL);
	ft_strlcpy(res, name, len + 1);
	if (has_equal)
	{
		ft_strlcat(res, "=", len + 1);
		if (value)
			ft_strlcat(res, value, len + 1);
	}
	return (res);
}

static int	export_check_name(char *arg, char *name, char *value)
{
	if (!is_valid_name(name))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(name);
		free(value);
		return (1);
	}
	return (0);
}

static void	init_name_and_value(char *arg, char **name, char **tmp)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq)
	{
		*name = ft_strndup(arg, eq - arg);
		*tmp = ft_strdup(eq + 1);
	}
	else
	{
		*name = ft_strdup(arg);
		*tmp = NULL;
	}
}

static int	export_process_arg(char *arg, t_line *line)
{
	char	*name;
	char	*tmp;
	char	*value;
	int		has_equal;
	char	*full;

	init_name_and_value(arg, &name, &tmp);
	has_equal = (tmp != NULL);
	if (export_check_name(arg, name, tmp))
		return (1);
	value = looking_in_local_vars(name, line);
	if (!value && !has_equal)
		value = get_env_value5(name, line);
	if (value)
		full = export_join(name, value, 1);
	else
		full = export_join(name, tmp, has_equal);
	free(tmp);
	if (!full || export_set_env(name, full, line))
		return (free(name), 1);
	free(name);
	return (0);
}

int	builtin_export(char **args, t_line *line)
{
	int	ret;
	int	i;

	ret = 0;
	if (!args[1])
		return (export_print_env(line));
	i = 1;
	while (args[i])
	{
		if (export_process_arg(args[i], line))
			ret = 1;
		i++;
	}
	return (ret);
}
