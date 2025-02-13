/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:30:34 by ekechedz          #+#    #+#             */
/*   Updated: 2024/04/24 16:35:13 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*last;
	unsigned char	search;

	search = (unsigned char) c;
	last = NULL;
	while (*s)
	{
		if (*s == search)
			last = (char *)s;
		s++;
	}
	if (search == '\0')
		return ((char *) s);
	return (last);
}
