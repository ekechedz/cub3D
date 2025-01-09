/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:33:27 by ekechedz          #+#    #+#             */
/*   Updated: 2024/04/24 19:18:38 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*mem;
	size_t		e;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	e = 0;
	if (i <= start)
		mem = malloc(sizeof(char));
	else
	{
		if (start + len > i)
			len = i - start;
		mem = (char *)malloc((len + 1) * sizeof(char));
		if (!mem)
			return (NULL);
		while (e < len)
		{
			mem[e] = s[start + e];
			e++;
		}
	}
	mem[e] = '\0';
	return (mem);
}
