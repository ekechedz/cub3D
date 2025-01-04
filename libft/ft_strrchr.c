/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:49:14 by phartman          #+#    #+#             */
/*   Updated: 2024/04/26 16:09:37 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			len;
	unsigned char	uc;

	uc = c;
	len = ft_strlen(s);
	if (uc == 0)
		return ((char *)&s[len]);
	while (len--)
	{
		if (s[len] == uc)
			return ((char *)&s[len]);
	}
	return (NULL);
}
