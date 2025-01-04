/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phartman <phartman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:28:04 by phartman          #+#    #+#             */
/*   Updated: 2024/05/06 16:44:23 by phartman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *str, char sep);
static size_t	ft_wordlen(const char *str, char sep);
static char		*ft_strndup(const char *s, size_t size);
static char		**ft_free(char **array, int index);

char	**ft_split(char const *s, char c)
{
	size_t	wordlen;
	size_t	word_i;
	char	**array;

	array = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	word_i = 0;
	while (1)
	{
		while (*s && *s == c)
			s++;
		if (!(*s))
			break ;
		wordlen = ft_wordlen(s, c);
		array[word_i++] = ft_strndup(s, wordlen);
		if (array[word_i -1] == NULL)
			return (ft_free(array, word_i -1));
		s = s + wordlen;
	}
	array[word_i] = NULL;
	return (array);
}

static size_t	ft_count_words(const char *str, char sep)
{
	size_t	count;

	count = 0;
	while (str && *str)
	{
		if (*str != sep)
		{
			count++;
			while (*str != sep && *str)
				str++;
		}
		if (*str)
			str++;
	}
	return (count);
}

static size_t	ft_wordlen(const char *str, char sep)
{
	size_t	count;

	count = 0;
	while (*str && *str != sep)
	{
		count++;
		str++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, size_t size)
{
	size_t	i;
	char	*dupstr;

	dupstr = (char *)malloc((size +1) * sizeof(char));
	if (dupstr == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dupstr[i] = s[i];
		i++;
	}
	dupstr[i] = '\0';
	return (dupstr);
}

static char	**ft_free(char **array, int index)
{
	while (index >= 0)
		free(array[index--]);
	free(array);
	return (NULL);
}

/*
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	char *str = "   Welcome   to   42   Berlin!   ";
	char sep = ' ';
	char **array = ft_split(str, sep);
	int	i;
	int	j;
	
	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			write(1, &array[i][j], 1);
			j++;
		}
		free(array[i]);
		write(1, "\n", 1);
		i++;
	}
	free(array);
}
*/