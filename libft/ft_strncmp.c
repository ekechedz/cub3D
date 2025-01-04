/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:32:52 by phartman          #+#    #+#             */
/*   Updated: 2024/04/26 16:05:14 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	uns1;
	unsigned char	uns2;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && (unsigned char)s1[i] == (unsigned char)s2[i])
	{
		if (!s2[i])
			return (0);
		i++;
	}
	uns1 = (unsigned char)s1[i];
	uns2 = (unsigned char)s2[i];
	return ((uns1 > uns2) - (uns1 < uns2));
}
