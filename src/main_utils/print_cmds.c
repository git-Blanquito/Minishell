/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishelll                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco almorene <marvin@42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/07/22 02:41:03 by aial             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_redir(t_redir *redir)
{
	while (redir)
	{
		printf("  redirection: ");
		if (redir->type == TOKEN_REDIR_IN)
			printf("<\n");
		else if (redir->type == TOKEN_REDIR_OUT)
			printf(">\n");
		else if (redir->type == TOKEN_APPEND)
			printf(">>\n");
		else if (redir->type == TOKEN_HEREDOC)
			printf("<<\n");
		else
			printf("unknown\n");
		printf("    file: %s\n", redir->filename);
		redir = redir->next;
	}
}

static void	print_argv(t_args **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
	{
		printf("  argv[%d]: ", i);
		if (argv[i]->was_single_quoted)
			printf("'%s'\n", argv[i]->value);
		else if (argv[i]->was_double_quoted)
			printf("\"%s\"\n", argv[i]->value);
		else
			printf("%s\n", argv[i]->value);
		i++;
	}
}

void	print_commands(t_cmd *cmds)
{
	int	i;

	i = 1;
	while (cmds)
	{
		printf("Command %d:\n", i);
		print_argv(cmds->argv);
		print_redir(cmds->redirs);
		cmds = cmds->next;
		i++;
	}
}
