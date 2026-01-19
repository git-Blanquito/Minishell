/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_type2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 17:13:01 by almorene          #+#    #+#             */
/*   Updated: 2025/11/22 21:20:24 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*pipe_syntax_error(t_cmd *curr)
{
	printf("minishell: syntax error near unexpected token `|'\n");
	g_last_status = 2;
	curr->error = 1;
	return (NULL);
}

static t_token	*handle_pipe(t_cmd **curr, t_token *tok)
{
	if (tok->type != TOKEN_PIPE)
		return (tok);
	if ((*curr)->argv == NULL || (*curr)->argv[0] == NULL)
		return (pipe_syntax_error(*curr));
	if (!tok->next && (*curr)->error != 1)
		return (pipe_syntax_error(*curr));
	if (tok->next->type == TOKEN_PIPE && (*curr)->error != 1)
		return (pipe_syntax_error(*curr));
	(*curr)->next = cmd_new();
	if (!(*curr)->next)
		(*curr)->error = 1;
	else
		*curr = (*curr)->next;
	return (tok);
}

static void	cleanup_on_error(t_cmd **curr, t_cmd **head)
{
	if (!curr || !head)
		return ;
	if (*curr && (*curr)->error == 1)
	{
		if (*head)
		{
			free_commands(*head);
			*head = NULL;
		}
		*curr = NULL;
	}
}

static t_token	*return_error(t_cmd **curr)
{
	if (curr && *curr)
		(*curr)->error = 1;
	return (NULL);
}

t_token	*parse_token_type(t_token *tok, t_cmd **curr,
			int *g_heredoc_index, t_cmd **head)
{
	if (!tok)
		return (NULL);
	tok = handle_word_or_string(tok, curr);
	if (!tok)
		return (return_error(curr));
	tok = handle_heredoc(tok, *curr, g_heredoc_index);
	if (!tok)
		return (return_error(curr));
	tok = handle_redir(tok, *curr);
	if (!tok)
		return (return_error(curr));
	tok = handle_pipe(curr, tok);
	if (!tok)
		return (return_error(curr));
	cleanup_on_error(curr, head);
	return (tok);
}
