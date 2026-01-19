/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:27:47 by almorene          #+#    #+#             */
/*   Updated: 2025/10/30 15:24:15 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_malloc_error(t_token *head,
		t_cmd *cmds, char *input, t_redir *redirs)
{
	t_redir	*tmp;

	write(2, "minishell: malloc failed\n", 26);
	if (head)
		free_token_list(head);
	if (cmds)
		free_commands(cmds);
	if (input)
		free(input);
	if (redirs)
	{
		while (redirs)
		{
			if (redirs->type == TOKEN_HEREDOC && redirs->filename)
				unlink(redirs->filename);
			free(redirs->filename);
			tmp = redirs->next;
			free(redirs);
			redirs = tmp;
		}
	}
	free_argv2(head->line->g_environ);
	exit(EXIT_FAILURE);
}
