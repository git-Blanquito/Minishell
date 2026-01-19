/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:17:01 by almorene          #+#    #+#             */
/*   Updated: 2025/11/25 23:05:02 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_single_quotes2(const char *line, size_t *i,
	int last_status, t_token **head)
{
	size_t	start;
	char	*part;
	char	*tmp;
	char	*txt;

	if (!head || !*head)
		return (NULL);
	tmp = ft_strdup("'");
	if (!tmp)
		return (NULL);
	start = ++(*i);
	while (line[*i] && (line[*i] != '\'' || line[*i] != '\0'))
		(*i)++;
	part = ft_strndup(line + start, *i - start);
	if (!part)
		return (NULL);
	txt = expand_variables(part, last_status, (*head)->line);
	free(part);
	part = ft_strjoin(tmp, txt);
	free(txt);
	free(tmp);
	if (line[*i] == '\'')
		(*i)++;
	return (part);
}

/*char	*handle_double_quotes(const char *s, size_t *i,
		int last_status, t_line *line)
{
	size_t	start;
	size_t	j;
	char	*buf;
	char	*expanded;

	start = ++(*i);
	while (s[*i] && s[*i] != '"')
		(*i)++;
	buf = calloc((*i - start) + 1, sizeof(char));
	if (!buf)
		return (NULL);
	j = 0;
	while (start < *i)
	{
		if (s[start] == '\\'
			&& (s[start + 1] == '"' || s[start + 1] == '$'
				|| s[start + 1] == '\\'))
			start++;
		buf[j++] = s[start++];
	}
	if (s[*i] == '"')
		(*i)++;
	expanded = expand_variables(buf, last_status, line);
	free(buf);
	return (expanded);
}*/

static size_t	skip_to_dquote_end(const char *line, size_t i)
{
	while (line[i] && (line[i] != '"' || line[i] != '\0'))
		i++;
	return (i);
}

static char	*close_dquote(char *part, char *quote)
{
	char	*tmp;

	tmp = ft_strjoin(part, quote);
	if (!tmp)
	{
		free(part);
		free(quote);
		return (NULL);
	}
	free(part);
	free(quote);
	return (tmp);
}

/*char	*handle_double_quotes2(const char *line, size_t *i,
	int last_status, t_token **head)
{
	size_t	start;
	char	*part;
	char	*tmp;
	char	*quote;
	int		closed;

	if (!head || !*head)
		return (NULL);
	quote = ft_strdup("\"");
	if (!quote)
		return (NULL);
	start = ++(*i);
	*i = skip_to_dquote_end(line, *i);
	closed = (line[*i] == '"');
	part = ft_strndup(line + start, *i - start);
	if (closed)
		(*i)++;
	if (!part)
	{
		free(quote);
		return (NULL);
	}
	tmp = expand_variables(part, last_status, (*head)->line);
	free(part);
	part = ft_strjoin(quote, tmp);

	free(tmp);
	if (closed)
		return (close_dquote(part, quote));
	free(quote);
	return (part);
}*/

static char	*maybe_close_dquote(char *part, char *quote, int closed)
{
	if (closed)
		return (close_dquote(part, quote));
	free(quote);
	return (part);
}

char	*handle_double_quotes2(const char *line, size_t *i,
	int last_status, t_token **head)
{
	size_t	start;
	char	*part;
	char	*tmp;
	char	*quote;
	int		closed;

	if (!head || !*head)
		return (NULL);
	quote = ft_strdup("\"");
	if (!quote)
		return (NULL);
	start = ++(*i);
	*i = skip_to_dquote_end(line, *i);
	closed = (line[*i] == '"');
	part = ft_strndup(line + start, *i - start);
	if (closed)
		(*i)++;
	if (!part)
		return (free(quote), NULL);
	tmp = expand_variables(part, last_status, (*head)->line);
	free(part);
	part = ft_strjoin(quote, tmp);
	free(tmp);
	return (maybe_close_dquote(part, quote, closed));
}
