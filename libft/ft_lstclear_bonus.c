/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aiblanco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:03:56 by aiblanco          #+#    #+#             */
/*   Updated: 2022/11/05 17:03:57 by aiblanco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;

	while (*lst)
	{
		list = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = list;
	}
}

/*
int	main(void)
{
	t_list *l = ft_lstnew(ft_strdup("nyancat"));
	l->next = ft_lstnew(ft_strdup("#TEST#"));
	ft_lstclear(&l, free);
	write(2, "", 1);
}
*/