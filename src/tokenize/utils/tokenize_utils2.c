/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:29 by almorene          #+#    #+#             */
/*   Updated: 2025/11/22 20:45:05 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_unquoted(char *input, size_t *i)
{
	char	*part;
	size_t	start;

	start = *i;
	while (input[*i] && !is_space(input[*i]) && !is_operator(input[*i])
		&& input[*i] != '"' && input[*i] != '\'')
		(*i)++;
	part = ft_strndup(&input[start], *i - start);
	if (!part)
		return (NULL);
	return (part);
}

void	create_and_add_token(t_quote_ctx *ctx,
	char *token_str, int was_single, int was_double)
{
	t_token	*new_token;

	if (!ctx)
	{
		free(token_str);
		return ;
	}
	new_token = token_new(TOKEN_WORD, token_str, was_single, was_double);
	free(token_str);
	if (!new_token)
		exit_malloc_error_tokens(ctx->head);
	new_token->line = ctx->line;
	token_add_back(ctx->head, new_token);
}

char	*expand_if_needed(char *part,
	int part_single, int last_status, t_quote_ctx *ctx)
{
	char	*expanded;

	if (part_single)
		return (part);
	expanded = expand_variables(part, last_status, ctx->line);
	free(part);
	if (!expanded)
		return (ft_strdup(""));
	return (expanded);
}
