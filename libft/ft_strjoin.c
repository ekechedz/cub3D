/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:56:40 by ekechedz          #+#    #+#             */
/*   Updated: 2024/04/25 15:37:54 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		a;
	int		b;
	char	*mem;

	a = ft_strlen(s1);
	b = ft_strlen(s2);
	mem = (char *)malloc(a + b +1);
	if (mem == NULL)
		return (NULL);
	ft_strcpy(mem, (char *) s1);
	ft_strcat(mem, (char *) s2);
	return (mem);
}
