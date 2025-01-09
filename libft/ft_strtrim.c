/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:39:33 by ekechedz          #+#    #+#             */
/*   Updated: 2024/04/25 17:55:27 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	char	*mem;
	int		len;
	int		end;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
	{
		start++;
	}
	end = ft_strlen(s1) - 1;
	while (end > start && ft_strchr(set, s1[end]))
	{
		end--;
	}
	len = end - start + 1;
	mem = (char *) malloc (sizeof(char) * (len + 1));
	if (!mem)
		return (NULL);
	ft_strlcpy(mem, s1 + start, len + 1);
	return (mem);
}
