/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:18:46 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/17 14:19:12 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			linelen;

	linelen = 0;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer[0] != '\0')
	{
		line = ft_rrealloc(line, (linelen) + BUFFER_SIZE + 1);
		line = append_buffer(buffer, line, &linelen);
	}
	if (line && line[linelen - 1] == '\n')
		return (line);
	line = getmyline(line, buffer, fd, &linelen);
	return (line);
}
