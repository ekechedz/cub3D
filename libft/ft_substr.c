/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:55:28 by phartman          #+#    #+#             */
/*   Updated: 2024/04/24 13:14:59 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	true_len;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	true_len = str_len - start;
	if (true_len > len)
		true_len = len;
	sub = malloc(true_len + 1);
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s + start, true_len);
	sub[true_len] = '\0';
	return (sub);
}
