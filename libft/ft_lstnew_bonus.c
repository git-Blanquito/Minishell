/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 19:25:41 by aiblanco          #+#    #+#             */
/*   Updated: 2022/10/31 19:25:43 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nodo;

	nodo = (t_list *) ft_calloc(sizeof(t_list), 1);
	if (!nodo)
	{
		return (NULL);
	}
	nodo->content = content;
	nodo->next = NULL;
	return (nodo);
}
