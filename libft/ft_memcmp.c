/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:54:41 by ekechedz          #+#    #+#             */
/*   Updated: 2024/04/24 16:16:40 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t num )
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;

	c1 = (unsigned char *) s1;
	c2 = (unsigned char *) s2;
	i = 0;
	if (num == 0)
		return (0);
	while (num > i)
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		c1++;
		c2++;
		i++;
	}
	return (0);
}
// #include <stdio.h>

// int main()
// {
//     char *s1 = "abc";
//     char *s2 = "abc";
//     printf("%d", ft_memcmp(s1, s2, 3));
//     return 0;
// }
