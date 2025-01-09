/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:02:29 by ekechedz          #+#    #+#             */
/*   Updated: 2024/11/18 20:04:49 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	char	*mem;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (count > SIZE_MAX / size)
		return (NULL);
	if (count > UINTPTR_MAX / size)
		return (NULL);
	total = count * size;
	mem = malloc(total);
	if (mem == NULL)
		return (NULL);
	if (mem != NULL)
		ft_memset(mem, 0, total);
	return (mem);
}

int main()
{
    {
        printf("Test 1: array of chars(5)\n");
        char *ptr; char *ptr2; size_t n = 5;
        ptr = (char *)ft_calloc(n, sizeof(char)); ptr2 = (char *)calloc(n, sizeof(char));
        for (size_t a = 0; a < n; a++)
            printf("%d", ptr[a]);
        printf(" | ");
        for (size_t a = 0; a < n; a++)
            printf("%d", ptr2[a]);
        free(ptr); free(ptr2);
    }
    printf("\n\n");
    {
        printf("Test 2: array of ints(5)\n");
        int *ptr; int *ptr2; size_t n = 5;
        ptr = (int *)ft_calloc(n, sizeof(int)); ptr2 = (int *)calloc(n, sizeof(int));
        for (size_t a = 0; a < n; a++)
            printf("%d", ptr[a]);
        printf(" | ");
        for (size_t a = 0; a < n; a++)
            printf("%d", ptr2[a]);
        free(ptr); free(ptr2);
    }
    printf("\n\n");
    {
        printf("Test 3: array of chars(SIZE_MAX)\n");
        char *ptr; /*char *ptr2;*/ size_t n = SIZE_MAX;
        ptr = (char *)ft_calloc(n, sizeof(char)); /*ptr2 = (char *)calloc(n, sizeof(char));*/
        for (size_t a = 0; a < n; a++)
            printf("%d", ptr[a]);
        printf(" | ");
        /*for (size_t a = 0; a < n; a++)
            printf("%d", ptr2[a]);*/
        free(ptr); /*free(ptr2);*/
    }
    printf("\n\n");
    {
        printf("Test 4: array of chars(SIZE_MAX + 1)\n");
        char *ptr; char *ptr2; size_t n = SIZE_MAX + 1;
        ptr = (char *)ft_calloc(n, sizeof(char)); ptr2 = (char *)calloc(n, sizeof(char));
        for (size_t a = 0; a < n; a++)
            printf("%d", ptr[a]);
        printf(" | ");
        for (size_t a = 0; a < n; a++)
            printf("%d", ptr2[a]);
        free(ptr); free(ptr2);
    }
    printf("\n\n");
    {
        printf("Test 5: array of ints(SIZE_MAX)\n");
        int *ptr; int *ptr2; size_t n = SIZE_MAX;
        ptr = (int *)ft_calloc(n, sizeof(int)); ptr2 = (int *)calloc(n, sizeof(int));
        for (size_t a = 0; a < n; a++)
            printf("%d", ptr[a]);
        printf(" | ");
        for (size_t a = 0; a < n; a++)
            printf("%d", ptr2[a]);
        free(ptr); free(ptr2);
    }
    printf("\n\n");
    return 0;
}
