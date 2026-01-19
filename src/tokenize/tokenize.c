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

static void	handle_pipe_token(t_token **head, size_t *i, t_line *line)
{
	t_token	*t;

	t = token_new(TOKEN_PIPE, "|", 0, 0);
	if (!t)
		exit_malloc_error_tokens(head);
	t->line = line;
	token_add_back(head, t);
	(*i)++;
}

static int	handle_redirect_token(t_token **head, char *input, size_t *i)
{
	if (handle_redirects(head, input, i))
		return (1);
	return (0);
}

static void	handle_word_token(t_token **head, t_word_args args)
{
	handle_word(head, args);
}

int	handle_redirects(t_token **head,
	char *input, size_t *i)
{
	if (input[*i] == '<' || input[*i] == '>')
	{
		if (input[*i] == '<' && input[*i + 1] == '<')
			add_double_operator_token(head, "<<", i, input);
		else if (input[*i] == '>' && input[*i + 1] == '>')
			add_double_operator_token(head, ">>", i, input);
		else if (input[*i] == '<')
			add_simple_operator_token(head, "<", i, input);
		else
			add_simple_operator_token(head, ">", i, input);
		return (1);
	}
	return (0);
}

t_token	*tokenize(char *input, int last_status, t_line *line)
{
	t_token		*head;
	size_t		i;
	t_word_args	args;

	args.input = input;
	args.i = &i;
	args.last_status = last_status;
	args.line = line;
	head = NULL;
	i = 0;
	while (input[i])
	{
		skip_spaces(input, &i);
		if (!input[i])
			break ;
		if (input[i] == '|')
			handle_pipe_token(&head, &i, line);
		else if (handle_redirect_token(&head, input, &i))
			continue ;
		else
			handle_word_token(&head, args);
	}
	return (head);
}
