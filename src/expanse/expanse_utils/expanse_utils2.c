/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:40:42 by almorene          #+#    #+#             */
/*   Updated: 2025/11/13 21:13:50 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_str(char *s, const char *t)
{
	char	*r;
	size_t	a;
	size_t	b;

	if (s)
		a = ft_strlen(s);
	else
		a = 0;
	if (t)
		b = ft_strlen(t);
	else
		b = 0;
	r = malloc(a + b + 1);
	if (!r)
	{
		free(s);
		return (NULL);
	}
	if (s)
		ft_memcpy(r, s, a);
	if (t)
		ft_memcpy(r + a, t, b);
	r[a + b] = '\0';
	free(s);
	return (r);
}

char	*append_ch(char *s, char c)
{
	size_t	a;
	char	*r;

	if (s)
		a = ft_strlen(s);
	else
		a = 0;
	r = malloc(a + 2);
	if (!r)
	{
		free(s);
		return (NULL);
	}
	if (s)
		ft_memcpy(r, s, a);
	r[a] = c;
	r[a + 1] = '\0';
	free(s);
	return (r);
}

char	*env_get(char *name, char **envp)
{
	size_t		i;
	size_t		len;
	char		*v;

	len = ft_strlen(name);
	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	v = get_env_value6(name, envp);
	if (v)
		return (v);
	return ("");
}

int	expand_home(const char *s, const char *p, t_exp_ctx *ctx)
{
	const char	*home;

	if ((p == s || *(p - 1) == ' ') && *p == '~')
	{
		if (!ctx->was_single_quoted)
		{
			if (*(p + 1) == '\0' || *(p + 1) == '/')
			{
				home = get_var(ctx->line, "HOME", ctx->envp);
				ctx->out = append_str(ctx->out, home);
				return (1);
			}
		}
	}
	return (0);
}

const char	*expand_dollar_end(const char *p, t_exp_ctx *ctx)
{
	ctx->out = append_ch(ctx->out, '$');
	return (p);
}
