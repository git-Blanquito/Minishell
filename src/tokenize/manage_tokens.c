/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/11/22 21:22:23 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(t_token_type type, char *value,
		int was_single_quoted, int was_double_quoted)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->was_single_quoted = was_single_quoted;
	token->was_double_quoted = was_double_quoted;
	token->next = NULL;
	token->line = NULL;
	return (token);
}

void	token_add_back(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static int	get_token_type(const char *value)
{
	if (!ft_strcmp(value, "|"))
		return (TOKEN_PIPE);
	if (!ft_strcmp(value, "<<"))
		return (TOKEN_HEREDOC);
	if (!ft_strcmp(value, ">>"))
		return (TOKEN_APPEND);
	if (!ft_strcmp(value, "<"))
		return (TOKEN_REDIR_IN);
	if (!ft_strcmp(value, ">"))
		return (TOKEN_REDIR_OUT);
	return (-1);
}

void	add_simple_operator_token(t_token **head,
		char *value, size_t *i, char *input)
{
	t_token	*new_token;
	t_line	*line;

	new_token = token_new(get_token_type(value), value, 0, 0);
	if (!new_token)
	{
		free(input);
		exit_malloc_error_tokens(head);
	}
	line = NULL;
	if (head && *head)
		line = (*head)->line;
	new_token->line = line;
	token_add_back(head, new_token);
	(*i)++;
}

void	add_double_operator_token(t_token **head,
		char *value, size_t *i, char *input)
{
	t_token	*new_token;
	t_line	*line;

	new_token = token_new(get_token_type(value), value, 0, 0);
	if (!new_token)
	{
		free(input);
		exit_malloc_error_tokens(head);
	}
	line = NULL;
	if (head && *head)
		line = (*head)->line;
	new_token->line = line;
	token_add_back(head, new_token);
	(*i) += 2;
}
