/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expans_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:01:51 by almorene          #+#    #+#             */
/*   Updated: 2025/11/22 21:23:54 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value(char **envp, const char *name)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*expand_hd_dollar(char *res, int *i, int last)
{
	char	*tmp;

	tmp = ft_itoa(last);
	if (!tmp)
		return (res);
	res = strjoin_free(res, tmp);
	free(tmp);
	(*i)++;
	return (res);
}

static char	*expand_hd_variable(const char *s, char *res,
			int *i, char **envp)
{
	size_t	start;
	char	*name;
	char	*val;

	start = *i;
	while (ft_isalnum(s[*i]) || s[*i] == '_')
		(*i)++;
	name = ft_strndup(s + start, *i - start);
	if (!name)
		return (res);
	val = get_env_value(envp, name);
	if (val)
		res = strjoin_free(res, val);
	free(name);
	return (res);
}

static char	*append_char_hd(const char *s, char *res, int *i)
{
	char	tmp[2];

	tmp[0] = s[*i];
	tmp[1] = 0;
	res = strjoin_free(res, tmp);
	(*i)++;
	return (res);
}

char	*expand_variables_heredoc(const char *s, int last, char **envp)
{
	char	*res;
	int		i;

	if (!s)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			if (s[i] == '?')
				res = expand_hd_dollar(res, &i, last);
			else if (ft_isalpha(s[i]) || s[i] == '_')
				res = expand_hd_variable(s, res, &i, envp);
			else
				res = strjoin_free(res, "$");
		}
		else
			res = append_char_hd(s, res, &i);
	}
	return (res);
}
