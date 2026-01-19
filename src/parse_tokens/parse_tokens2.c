/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:00:47 by almorene          #+#    #+#             */
/*   Updated: 2025/11/10 20:01:34 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_add_redir(t_cmd *cmd, t_token_type type, char *filename)
{
	t_redir	*redir;
	t_redir	*tmp;

	redir = redir_new(type, filename);
	if (!redir)
	{
		ft_printf("Malloc error\n");
		cmd->error = 1;
		return ;
	}
	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

int	is_single_quoted(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	if (len >= 2 && s[0] == '\'' && s[len - 1] == '\'')
		return (1);
	return (0);
}

int	get_expand_flag(t_token *next)
{
	if (next->was_single_quoted || next->was_double_quoted)
		return (0);
	return (1);
}
