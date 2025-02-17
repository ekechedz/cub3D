/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:02:29 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/17 14:18:01 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	char	*mem;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (count > SIZE_MAX / size)
		return (NULL);
	if (count > UINTPTR_MAX / size)
		return (NULL);
	total = count * size;
	mem = malloc(total);
	if (mem == NULL)
		return (NULL);
	if (mem != NULL)
		ft_memset(mem, 0, total);
	return (mem);
}
