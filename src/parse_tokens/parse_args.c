/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:41:00 by aial              #+#    #+#             */
/*   Updated: 2025/10/23 00:32:36 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_first_arg(t_cmd *cmd, t_token *tok)
{
	cmd->argv = malloc(sizeof(t_args *) * 2);
	if (!cmd->argv)
	{
		cmd->error = 1;
		return ;
	}
	cmd->argv[0] = new_arg(tok->value,
			tok->was_single_quoted,
			tok->was_double_quoted);
	if (!cmd->argv[0])
	{
		cmd->error = 1;
		return ;
	}
	cmd->argv[1] = NULL;
}

static t_args	**copy_and_expand_argv(t_cmd *cmd, int count)
{
	t_args	**new_argv;
	int		j;

	new_argv = malloc(sizeof(t_args *) * (count + 2));
	if (!new_argv)
	{
		cmd->error = 1;
		return (NULL);
	}
	j = 0;
	while (j < count)
	{
		new_argv[j] = cmd->argv[j];
		j++;
	}
	new_argv[count] = NULL;
	return (new_argv);
}

static void	append_arg(t_cmd *cmd, t_token *tok)
{
	int		i;
	t_args	**new_argv;

	i = 0;
	while (cmd->argv[i])
		i++;
	new_argv = copy_and_expand_argv(cmd, i);
	if (!new_argv)
		return ;
	new_argv[i] = new_arg(tok->value,
			tok->was_single_quoted,
			tok->was_double_quoted);
	if (!new_argv[i])
	{
		cmd->error = 1;
		free(new_argv);
		return ;
	}
	new_argv[i + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

void	cmd_add_argv(t_cmd *cmd, t_token *tok)
{
	if (!cmd->argv)
		init_first_arg(cmd, tok);
	else
		append_arg(cmd, tok);
}
