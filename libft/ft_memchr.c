/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:59:00 by phartman          #+#    #+#             */
/*   Updated: 2024/04/24 15:01:59 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*mem;
	size_t			i;

	i = 0;
	mem = (unsigned char *)s;
	while (i < n)
	{
		if (mem[i] == (unsigned char)c)
		{
			return (&mem[i]);
		}
		i++;
	}
	return (NULL);
}
