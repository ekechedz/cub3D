/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:36:11 by ekechedz          #+#    #+#             */
/*   Updated: 2024/04/23 12:34:08 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*e;

	e = (unsigned char *) b;
	while (len > 0)
	{
		*e++ = (unsigned char) c;
		len--;
	}
	return (b);
}
/*#include <stdio.h>
#include <string.h>
int main() {
    char str[20];
    size_t len = 10;
    int c = 'X';

    ft_memset(str, c, len);

    printf("Result of ft_memset: %s\n", str);

    char str_std[20];
    memset(str_std, c, len);

    if (strcmp(str, str_std) == 0) {
        printf("ft_memset matches memset\n");
    } else {
        printf("ft_memset doesn't match memset\n");
    }

    return 0;
}*/
