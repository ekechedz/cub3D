/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:51:53 by phartman          #+#    #+#             */
/*   Updated: 2024/04/25 15:47:48 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*memdest;
	const unsigned char	*memsrc;
	size_t				i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	memdest = dest;
	memsrc = src;
	while (i < n)
	{
		if (dest <= src)
			memdest[i] = memsrc[i];
		if (dest > src)
			memdest[n - 1 - i] = memsrc[n - 1 - i];
		i++;
	}
	return (dest);
}
