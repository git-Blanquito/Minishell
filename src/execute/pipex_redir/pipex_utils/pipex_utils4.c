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

void	cleanup_heredocs(t_redir *rlist)
{
	while (rlist)
	{
		if (rlist->type == TOKEN_HEREDOC && rlist->filename)
		{
			unlink(rlist->filename);
			free(rlist->filename);
			rlist->filename = NULL;
		}
		rlist = rlist->next;
	}
}

int	count_args(t_args **argv)
{
	int	count;

	count = 0;
	while (argv && argv[count])
		count++;
	return (count);
}

char	*process_raw_segment(const char *line, size_t *i,
			int last, t_line *pline)
{
	size_t	start;
	char	*raw;
	char	*expanded;

	start = *i;
	while (line[*i] && line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	raw = ft_strndup(line + start, *i - start);
	if (!raw)
		return (NULL);
	expanded = expand_variables_heredoc(raw, last, pline->g_environ);
	free(raw);
	return (expanded);
}
