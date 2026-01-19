/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:40:42 by almorene          #+#    #+#             */
/*   Updated: 2025/11/11 21:41:26 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_local_var(t_line *line, char *name, char *value)
{
	t_local_var	*v;
	t_local_var	*newv;

	v = line->local_vars;
	while (v)
	{
		if (!ft_strcmp(v->name, name))
		{
			free(v->value);
			v->value = ft_strdup(value);
			return ;
		}
		v = v->next;
	}
	newv = malloc(sizeof(*newv));
	if (!newv)
		return ;
	newv->name = ft_strdup(name);
	newv->value = ft_strdup(value);
	newv->next = line->local_vars;
	line->local_vars = newv;
}

char	*get_var(t_line *line, char *name, char **envp)
{
	t_local_var	*v;

	v = line->local_vars;
	while (v)
	{
		if (!ft_strcmp(v->name, name))
			return (v->value);
		v = v->next;
	}
	return (env_get(name, envp));
}
