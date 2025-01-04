/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:53:08 by ekechedz          #+#    #+#             */
/*   Updated: 2024/05/27 16:22:24 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

char		*get_next_line(int fd);
size_t		gnl_strlen(const char *str);
char		*gnl_strchr(const char *s, int c);
void		*gnl_memmove(void *dest, const void *src, size_t n);
char		*gnl_strncpy(char *dest, const char *src, size_t n);

#endif