/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:19:08 by ekechedz          #+#    #+#             */
/*   Updated: 2024/05/08 20:00:45 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;

	if (!lst)
		return (NULL);
	node = ft_lstnew((*f)(lst -> content));
	if (!node)
		return (NULL);
	if (lst -> next)
	{
		node -> next = ft_lstmap(lst -> next, f, del);
		if (!(node -> next))
		{
			ft_lstdelone(node, del);
			return (NULL);
		}
	}
	return (node);
}
