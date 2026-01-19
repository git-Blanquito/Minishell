/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:40:42 by almorene          #+#    #+#             */
/*   Updated: 2025/11/05 20:45:58 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*expand_last_status(const char *p, t_exp_ctx *ctx)
{
	char	*st;

	st = itoa_status(ctx->last_status);
	ctx->out = append_str(ctx->out, st);
	free(st);
	return (p + 1);
}

const char	*expand_name_var(const char *p, t_exp_ctx *ctx)
{
	char		name[256];
	size_t		len;
	const char	*start;
	const char	*val;

	start = p;
	while (is_name_char((unsigned char)*p))
		p++;
	len = (size_t)(p - start);
	if (len >= sizeof(name))
		len = sizeof(name) - 1;
	ft_memcpy(name, start, len);
	name[len] = '\0';
	val = get_var(ctx->line, name, ctx->envp);
	ctx->out = append_str(ctx->out, val);
	return (p);
}

const char	*expand_variable(const char *p, t_exp_ctx *ctx)
{
	if (*p == '\0')
		return (expand_dollar_end(p, ctx));
	if (*p == '?')
		return (expand_last_status(p, ctx));
	if (is_name_start((unsigned char)*p))
		return (expand_name_var(p, ctx));
	return (expand_dollar_end(p, ctx));
}

const char	*expand_char(const char *p, t_exp_ctx *ctx)
{
	ctx->out = append_ch(ctx->out, *p);
	return (p + 1);
}

char	*expand_str(const char *s, t_exp_ctx *ctx)
{
	const char	*p;

	if (!s)
		return (NULL);
	if (ctx->was_single_quoted)
		return (xstrdup(s));
	ctx->out = NULL;
	p = s;
	while (*p)
	{
		if (!ctx->was_single_quoted && expand_home(s, p, ctx))
			p++;
		else if (!ctx->was_single_quoted && *p == '$')
			p = expand_variable(p + 1, ctx);
		else
			p = expand_char(p, ctx);
	}
	if (!ctx->out)
		return (xstrdup(""));
	return (ctx->out);
}
