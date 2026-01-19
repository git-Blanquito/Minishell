/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/11/22 20:53:57 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_next_token(t_token *next, t_cmd *cmd)
{
	if (!next || !(next->type == TOKEN_WORD || next->type == TOKEN_STRING))
	{
		cmd->error = 1;
		return (0);
	}
	return (1);
}

int	parse_heredoc(t_token **tokt_cmd, t_cmd *cmd, int *g_heredoc_index)
{
	t_token	*next;
	char	*delim;
	char	*filename;
	int		expand_vars;
	t_line	*line;

	if (!tokt_cmd || !*tokt_cmd)
		return (0);
	line = (*tokt_cmd)->line;
	next = (*tokt_cmd)->next;
	if (!validate_next_token(next, cmd))
		return (0);
	expand_vars = get_expand_flag(next);
	delim = ft_strdup(next->value);
	if (!delim)
		return (cmd->error = 1, 0);
	filename = create_heredoc(delim, (*g_heredoc_index)++, expand_vars, line);
	free(delim);
	if (!filename)
		return (cmd->error = 1, 0);
	cmd_add_redir(cmd, TOKEN_REDIR_IN, filename);
	free(filename);
	*tokt_cmd = next;
	return (1);
}

t_token	*parse_redir(t_token *tok, t_cmd *cmd)
{
	t_token	*next;

	next = tok->next;
	if (next && (next->type == TOKEN_WORD || next->type == TOKEN_STRING))
	{
		cmd_add_redir(cmd, tok->type, next->value);
		return (next);
	}
	cmd->error = 1;
	if (tok->type == TOKEN_REDIR_IN || tok->type == TOKEN_HEREDOC)
	{
		g_last_status = 2;
		printf("minishell: syntax error near unexpected token `<'\n");
	}
	else
	{
		g_last_status = 2;
		printf("minishell: syntax error near unexpected token `>'\n");
	}
	return (NULL);
}

static t_cmd	*create_cmd_if_needed(t_cmd **curr, t_cmd **head)
{
	if (!*curr)
	{
		*curr = cmd_new();
		if (!*curr)
		{
			if (*head)
				free_commands(*head);
			*head = NULL;
			return (NULL);
		}
		if (!*head)
			*head = *curr;
	}
	return (*curr);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*curr;
	int		g_heredoc_index;

	head = NULL;
	curr = NULL;
	g_heredoc_index = 0;
	while (tokens)
	{
		if (!create_cmd_if_needed(&curr, &head))
			return (NULL);
		tokens = parse_token_type(tokens, &curr, &g_heredoc_index, &head);
		if (!tokens || (curr && curr->error))
		{
			if (head)
				free_commands(head);
			return (NULL);
		}
		tokens = tokens->next;
	}
	return (head);
}
