/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/09/29 22:46:38 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	cmd->error = 0;
	return (cmd);
}

t_redir	*redir_new(t_token_type type, char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = ft_strdup(filename);
	if (!redir->filename)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

t_args	*new_arg(const char *word,
						int was_single_quoted,
						int was_double_quoted)
{
	t_args	*arg;

	arg = malloc(sizeof(t_args));
	if (!arg)
		return (NULL);
	arg->value = ft_strdup(word);
	if (!arg->value)
	{
		free(arg);
		return (NULL);
	}
	arg->was_single_quoted = was_single_quoted;
	arg->was_double_quoted = was_double_quoted;
	return (arg);
}
