/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:36:28 by ekechedz          #+#    #+#             */
/*   Updated: 2024/04/24 16:19:19 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	search;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	search = (unsigned char)c;
	while (i < n)
	{
		if (*(ptr + i) == search)
			return (ptr + i);
		i++;
	}
	return (NULL);
}
