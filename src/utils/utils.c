#include "../../include/cub3d.h"

#include <stddef.h> // For size_t

char *ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

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
	return dest;
}

#include <stdlib.h>
#include <stdio.h>

void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return NULL;
	}
	if (!ptr)
	{
		new_ptr = malloc(new_size);
		if (!new_ptr)
		{
			perror("Failed to allocate memory");
			return NULL;
		}
		return new_ptr;
	}
	if (new_size <= old_size)
	{
		new_ptr = realloc(ptr, new_size);
		if (!new_ptr)
		{
			perror("Failed to reallocate memory");
			return NULL;
		}
		return new_ptr;
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
	{
		perror("Failed to allocate memory");
		return NULL;
	}
	size_t i = 0;
	while (i < old_size)
	{
		((char *)new_ptr)[i] = ((char *)ptr)[i];
		i++;
	}
	free(ptr);
	return new_ptr;
}
