/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 21:49:24 by almorene          #+#    #+#             */
/*   Updated: 2025/11/22 21:25:06 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*handle_word_or_string(t_token *tok, t_cmd **curr)
{
	if (tok->type == TOKEN_WORD || tok->type == TOKEN_STRING)
		cmd_add_argv(*curr, tok);
	return (tok);
}

t_token	*handle_heredoc(t_token *tok, t_cmd *curr, int *g_heredoc_index)
{
	t_token	*next;

	if (tok->type == TOKEN_HEREDOC)
	{
		next = tok->next;
		if (!next || next->type != TOKEN_WORD)
		{
			ft_putstr_fd("minishell:syntax error near unespected token\n", 2);
			return (NULL);
		}
		if (next && next->type == TOKEN_WORD)
		{
			if (!parse_heredoc(&tok, curr, g_heredoc_index))
				return (NULL);
		}
	}
	return (tok);
}

t_token	*handle_redir(t_token *tok, t_cmd *curr)
{
	if (tok->type == TOKEN_REDIR_IN
		|| tok->type == TOKEN_REDIR_OUT
		|| tok->type == TOKEN_APPEND)
		tok = parse_redir(tok, curr);
	return (tok);
}
