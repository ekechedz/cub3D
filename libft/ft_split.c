/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:36:14 by ekechedz          #+#    #+#             */
/*   Updated: 2024/04/30 14:15:19 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_substrings(char const *s, char c)
{
	int	count;
	int	in_substring;

	count = 0;
	in_substring = 0;
	while (*s)
	{
		if (*s == c)
			in_substring = 0;
		else if (!in_substring)
		{
			count++;
			in_substring = 1;
		}
		s++;
	}
	return (count);
}

char	*copy_substring(char const *start, int len)
{
	char	*sub;
	int		i;

	sub = (char *) malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = *start;
		start++;
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	**free_mem(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int				num_sub;
	char			**res;
	const char		*start;
	int				j;

	num_sub = count_substrings(s, c);
	res = (char **)malloc ((num_sub + 1) * sizeof(char *));
	j = 0;
	while (*s && j < num_sub)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		start = s;
		while (*s && *s != c)
			s++;
		res[j] = copy_substring(start, s - start);
		if (!res[j])
			return (free_mem(res));
		j++;
	}
	res[j] = NULL;
	return (res);
}
