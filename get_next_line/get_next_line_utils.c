/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:18:36 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/17 14:18:41 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*getmyline(char *line, char *buffer, int fd, int *linelen)
{
	int	b;

	b = read(fd, buffer, BUFFER_SIZE);
	while (b > 0)
	{
		(buffer)[b] = '\0';
		line = ft_rrealloc(line, (*linelen) + BUFFER_SIZE + 1);
		line = append_buffer(buffer, line, linelen);
		if (line && line[*linelen - 1] == '\n')
			return (line);
		b = read(fd, buffer, BUFFER_SIZE);
	}
	if (b == 0 && *linelen > 0)
	{
		return (line);
	}
	free(line);
	return (NULL);
}

char	*append_buffer(char *buffer, char *line, int *linelen)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((buffer)[i] != '\0')
	{
		line[*linelen] = (buffer)[i];
		i++;
		(*linelen)++;
		if (line[*linelen - 1] == '\n')
		{
			while ((buffer)[j + i] != '\0')
			{
				(buffer)[j] = (buffer)[j + i];
				j++;
			}
			buffer[j] = '\0';
			line[*linelen] = '\0';
			return (line);
		}
	}
	buffer[0] = '\0';
	line[*linelen] = '\0';
	return (line);
}

char	*ft_rrealloc(char *ptr, size_t size)
{
	char	*newptr;
	size_t	i;

	newptr = (char *)malloc(size);
	if (!newptr)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr)
	{
		i = 0;
		while (i < size - 1 && ptr[i] != '\0')
		{
			newptr[i] = ptr[i];
			i++;
		}
		free(ptr);
	}
	return (newptr);
}
