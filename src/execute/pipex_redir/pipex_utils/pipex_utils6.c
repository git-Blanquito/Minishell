/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:17:01 by almorene          #+#    #+#             */
/*   Updated: 2025/11/10 20:29:24 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**build_execve_argv(t_args **args)
{
	int		argc;
	char	**exec_argv;
	int		i;

	argc = count_args(args);
	exec_argv = malloc(sizeof(char *) * (argc + 1));
	if (!exec_argv)
		handle_malloc_error(NULL, NULL, NULL, NULL);
	i = 0;
	while (i < argc)
	{
		exec_argv[i] = ft_strdup(args[i]->value);
		if (!exec_argv[i])
		{
			while (i-- > 0)
				free(exec_argv[i]);
			free(exec_argv);
			handle_malloc_error(NULL, NULL, NULL, NULL);
		}
		i++;
	}
	exec_argv[argc] = NULL;
	return (exec_argv);
}

char	*gen_heredoc_filename(int index)
{
	char	*num;
	char	*filename;

	num = ft_itoa(index);
	if (!num)
		handle_malloc_error(NULL, NULL, NULL, NULL);
	filename = ft_strjoin("/tmp/minishell_heredoc_", num);
	free(num);
	if (!filename)
		handle_malloc_error(NULL, NULL, NULL, NULL);
	return (filename);
}

char	*handle_single_quotes(const char *line, size_t *i)
{
	size_t	start;
	char	*part;

	start = ++(*i);
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	part = ft_strndup(line + start, *i - start);
	if (line[*i] == '\'')
		(*i)++;
	return (part);
}
