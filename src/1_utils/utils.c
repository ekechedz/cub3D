/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:43:12 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/13 14:53:00 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <stddef.h>

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("Failed to allocate memory");
		return (NULL);
	}
	return (ptr);
}

void	*ft_resize(void *ptr, size_t new_size)
{
	void	*new_ptr;
	size_t	i;

	new_ptr = ft_malloc(new_size);
	if (!new_ptr)
		return (NULL);
	i = 0;
	while (i < new_size)
	{
		((char *)new_ptr)[i] = ((char *)ptr)[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}

void	*ft_expand(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	i;

	new_ptr = ft_malloc(new_size);
	if (!new_ptr)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		((char *)new_ptr)[i] = ((char *)ptr)[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (ft_malloc(new_size));
	if (new_size <= old_size)
		return (ft_resize(ptr, new_size));
	return (ft_expand(ptr, old_size, new_size));
}
