/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/11/22 21:22:03 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_word(t_token **head, t_word_args args)
{
	t_quote_ctx	ctx;
	char		*token_str;
	int			was_single;
	int			was_double;

	was_single = 0;
	was_double = 0;
	ctx.was_single = &was_single;
	ctx.was_double = &was_double;
	ctx.head = head;
	ctx.input = args.input;
	ctx.line = args.line;
	process_word_loop(args.i, ctx, &token_str, args.last_status);
	if (token_str)
		create_and_add_token(&ctx, token_str, was_single, was_double);
}

char	*strjoin_free(char *s1, char *s2)
{
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*process_quoted(size_t *i, t_quote_ctx ctx,
			int *out_was_single, int *out_was_double)
{
	char	*part;
	size_t	start;
	char	quote;

	*out_was_single = 0;
	*out_was_double = 0;
	quote = (ctx.input)[(*i)++];
	start = *i;
	while ((ctx.input)[*i] && (ctx.input)[*i] != quote)
		(*i)++;
	if ((ctx.input)[*i] == quote)
	{
		part = ft_strndup(&(ctx.input)[start], *i - start);
		if (!part)
			return (NULL);
		(*i)++;
		if (quote == '\'')
			*out_was_single = 1;
		else
			*out_was_double = 1;
		return (part);
	}
	free_token_list(*ctx.head);
	*ctx.head = NULL;
	return (NULL);
}
