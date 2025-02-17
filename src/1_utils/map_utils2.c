/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:06:59 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/17 14:12:50 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	all_keys_used(char *used_keys[MAX_KEYS])
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < MAX_KEYS)
	{
		if (used_keys[i] != NULL)
			count++;
		i++;
	}
	return (count == 6);
}

int	parse_single_color_component(const char **str)
{
	int	num;

	num = 0;
	while (**str == ' ')
		(*str)++;
	if (!ft_isdigit(**str))
		return (-1);
	num = parse_int(str);
	if (num < 0 || num > 255)
		return (-1);
	return (num);
}

int	check_and_skip_comma(const char **str)
{
	while (**str == ' ')
		(*str)++;
	if (**str == ',')
	{
		(*str)++;
		return (1);
	}
	return (0);
}
