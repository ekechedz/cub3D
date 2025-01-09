/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 18:11:19 by ekechedz          #+#    #+#             */
/*   Updated: 2024/05/08 19:09:53 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*e;

	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst)
	{
		e = (*lst)-> next;
		ft_lstdelone(*lst, del);
		*lst = e;
	}
}
