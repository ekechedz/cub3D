/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:33:39 by ekechedz          #+#    #+#             */
/*   Updated: 2024/04/24 16:06:41 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = ft_strlen(needle);
	if (i == 0)
		return ((char *) haystack);
	while ((i <= len) && *haystack)
	{
		if (ft_strncmp(haystack, needle, i) == 0)
			return ((char *) haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
// #include <stdio.h>
// int main()
// {
//     const char *i = "Hello world";
//     const char *s = "world";
//     size_t e = 13; 

//     printf("%s",ft_strnstr(i, s, e));
//     return 0;
// }
