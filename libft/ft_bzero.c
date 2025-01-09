/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:17:51 by ekechedz          #+#    #+#             */
/*   Updated: 2024/04/23 12:18:22 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len);

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
// #include <stdio.h>
// #include <string.h>

// int main() {
//     char str[20];
//     size_t len = 10;

//     ft_bzero(str, len);

//     printf("Result after ft_bzero: \"%s\"\n", str);

//     char str_std[20];
//     memset(str_std, 0, len);

//     printf("%s\n", memcmp(str, str_std, len) == 0 
//  ? "ft_bzero matches memset" : "ft_bzero doesn't match memset");

//     return 0;
// }
