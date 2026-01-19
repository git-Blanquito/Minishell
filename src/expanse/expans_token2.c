/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expans_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:01:51 by almorene          #+#    #+#             */
/*   Updated: 2025/11/22 21:23:54 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variables(const char *s, int last_status, t_line *line)
{
	t_exp_ctx	ctx;

	if (!s)
		return (NULL);
	ctx.line = line;
	ctx.last_status = last_status;
	ctx.was_single_quoted = 0;
	ctx.was_double_quoted = 0;
	ctx.envp = line->g_environ;
	ctx.out = NULL;
	return (expand_str(s, &ctx));
}
