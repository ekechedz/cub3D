/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:37:43 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/17 10:31:26 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
