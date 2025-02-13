/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:43:05 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/13 14:56:31 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	apply_shading(int i, int j, int color)
{
	if (i == 0 || j == 0 || i == MINIMAP_SCALE - 1 || j == MINIMAP_SCALE - 1)
		return (color / 2);
	else
		return (color);
}

void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	pixel_x;
	int	pixel_y;
	int	shade;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			pixel_x = x + i;
			pixel_y = y + j;
			if (pixel_x < WIN_WIDTH && pixel_y < WIN_HEIGHT)
			{
				shade = apply_shading(i, j, color);
				game->screen_data[pixel_y * WIN_WIDTH + pixel_x] = shade;
			}
			j++;
		}
		i++;
	}
}

int	check_for_wall_collision(t_game *game, int x0, int y0)
{
	int	map_x;
	int	map_y;

	map_x = (x0 - MINIMAP_X_OFFSET) / MINIMAP_SCALE;
	map_y = (y0 - MINIMAP_Y_OFFSET) / MINIMAP_SCALE;
	if (map_x >= 0 && map_x < game->map->width \
		&& map_y >= 0 && map_y < game->map->height
		&& game->map->grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\v' || c == '\f' || c == '\r');
}

void	trim_whitespace(char *str)
{
	int	start;
	int	end;
	int	i;

	if (str == NULL)
		return ;
	start = 0;
	end = ft_strlen(str) - 1;
	while (ft_isspace((unsigned char)str[start]))
		start++;
	while (end > start && ft_isspace((unsigned char)str[end]))
		end--;
	i = 0;
	while (start <= end)
		str[i++] = str[start++];
	str[i] = '\0';
}
