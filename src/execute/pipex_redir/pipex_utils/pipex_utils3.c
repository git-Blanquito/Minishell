/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:28:33 by almorene          #+#    #+#             */
/*   Updated: 2025/11/25 20:26:36 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_next_part(const char *line, size_t *i,
			int last, t_line *pline)
{
	t_token	**head;

	if (!pline)
		return (NULL);
	head = &pline->tokens;
	if (line[*i] == '\'')
		return (handle_single_quotes2(line, i, last, head));
	if (line[*i] == '"')
		return (handle_double_quotes2(line, i, last, head));
	return (process_raw_segment(line, i, last, pline));
}

static char	*append_part(char *result, char *part)
{
	char	*tmp;

	if (!part)
		return (result);
	tmp = strjoin_free(result, part);
	free(part);
	return (tmp);
}

char	*expand_heredoc_line(const char *line, int last, t_line *pline)
{
	char	*result;
	char	*part;
	size_t	i;

	result = NULL;
	i = 0;
	while (line[i])
	{
		part = expand_next_part(line, &i, last, pline);
		result = append_part(result, part);
	}
	if (!result)
		result = ft_strdup("");
	if (!result)
		return (NULL);
	return (result);
}

int	get_exit_status_from_wait(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
