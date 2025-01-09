/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:04:49 by ekechedz          #+#    #+#             */
/*   Updated: 2024/04/24 16:20:37 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	unsigned int	i;

	i = (unsigned int) c;
	if (i <= 127)
		return (1);
	return (0);
}

/*#include <stdio.h>
#include <ctype.h>

int main() {
    char ch = '5';

    if (ft_isascii(ch)) {
        printf("%c is an ASCII character.\n", ch);
    } else {
        printf("%c is not an ASCII character.\n", ch);
    }

    return 0;
}*/
