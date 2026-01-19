/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:07:19 by almorene          #+#    #+#             */
/*   Updated: 2025/11/22 20:46:47 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	join_and_free(char **token_str, char *to_join)
{
	char	*tmp;

	if (!*token_str)
		*token_str = to_join;
	else
	{
		tmp = ft_strjoin(*token_str, to_join);
		free(*token_str);
		free(to_join);
		*token_str = tmp;
	}
}

static void	update_flags(int *all_single, int *has_double,
	int part_single, int part_double)
{
	if (!part_single)
		*all_single = 0;
	if (part_double)
		*has_double = 1;
}

static void	process_part(size_t *i, t_quote_ctx ctx,
	char **part, int *s_d)
{
	if (ctx.input[*i] == '"' || ctx.input[*i] == '\'')
		*part = process_quoted(i, ctx, &s_d[0], &s_d[1]);
	else
		*part = process_unquoted(ctx.input, i);
}

static void	update_single_double(t_quote_ctx ctx,
	int all_s, int has_d)
{
	if (ctx.was_single)
		*ctx.was_single = all_s;
	if (ctx.was_double)
		*ctx.was_double = has_d;
}

void	process_word_loop(size_t *i,
	t_quote_ctx ctx, char **token_str, int last_status)
{
	char	*part;
	int		s_d[2];
	int		all_s;
	int		has_d;

	*token_str = NULL;
	all_s = 1;
	has_d = 0;
	while (ctx.input[*i] && !is_space(ctx.input[*i])
		&& !is_operator(ctx.input[*i]))
	{
		s_d[0] = 0;
		s_d[1] = 0;
		process_part(i, ctx, &part, s_d);
		if (!part)
			return ;
		part = expand_if_needed(part, s_d[0], last_status, &ctx);
		join_and_free(token_str, part);
		update_flags(&all_s, &has_d, s_d[0], s_d[1]);
	}
	update_single_double(ctx, all_s, has_d);
}
