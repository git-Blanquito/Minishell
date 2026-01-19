/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:38:16 by aiblanco          #+#    #+#             */
/*   Updated: 2022/11/05 17:38:18 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nodo;
	t_list	*first;

	if (!lst || !f || !del)
		return (NULL);
	nodo = ft_lstnew(f(lst->content));
	if (!nodo)
	{
		ft_lstdelone(nodo, del);
		return (NULL);
	}
	lst = lst->next;
	first = nodo;
	while (lst != NULL)
	{
		nodo->next = ft_lstnew(f(lst->content));
		if (!nodo->next)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		nodo = nodo->next;
		lst = lst->next;
	}
	return (first);
}
