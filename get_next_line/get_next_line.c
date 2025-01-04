/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:37:43 by ekechedz          #+#    #+#             */
/*   Updated: 2024/09/10 17:39:12 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) *((gnl_strlen(left_str)+gnl_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[gnl_strlen(left_str) + gnl_strlen(buff)] = '\0';
	free(left_str);
	return (str);
}

static char	*extract_line(char **buffer)
{
	char	*line_end;
	char	*line;
	size_t	len;

	line_end = gnl_strchr(*buffer, '\n');
	if (line_end)
	{
		len = line_end - *buffer + 1;
		line = malloc(len + 1);
		if (!line)
			return (NULL);
		gnl_strncpy(line, *buffer, len);
		line[len] = '\0';
		gnl_memmove(*buffer, *buffer + len, gnl_strlen(*buffer) - len + 1);
	}
	else
	{
		line = *buffer;
		*buffer = NULL;
	}
	return (line);
}

static char	fun_return(void *ptr)
{
	free(ptr);
	return (-1);
}

static int	read_to_buffer(int fd, char **buffer)
{
	char	*temp_buffer;
	ssize_t	bytes_read;
	char	*eoln_pointer;

	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (-1);
	eoln_pointer = gnl_strchr(*buffer, '\n');
	while (!eoln_pointer)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (fun_return(temp_buffer));
		if (bytes_read == 0)
			break ;
		temp_buffer[bytes_read] = '\0';
		*buffer = ft_strjoin(*buffer, temp_buffer);
		if (!*buffer)
			return (fun_return(temp_buffer));
		eoln_pointer = gnl_strchr(*buffer, '\n');
	}
	free(temp_buffer);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read_to_buffer(fd, &buffer) < 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	if (buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = extract_line(&buffer);
	return (line);
}
