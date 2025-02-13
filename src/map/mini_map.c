/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:42:49 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/13 17:31:12 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	clamp_to_minimap(int *x, int *y, t_game *game)
{
	int	min_x;
	int	min_y;
	int	max_x;
	int	max_y;

	min_x = MINIMAP_X_OFFSET;
	min_y = MINIMAP_Y_OFFSET;
	max_x = MINIMAP_X_OFFSET + (game->map->width * MINIMAP_SCALE);
	max_y = MINIMAP_Y_OFFSET + (game->map->height * MINIMAP_SCALE);
	if (*x < min_x)
		*x = min_x;
	if (*y < min_y)
		*y = min_y;
	if (*x > max_x)
		*x = max_x;
	if (*y > max_y)
		*y = max_y;
}

void	render_map_tiles(t_game *game)
{
	int		x;
	int		y;
	int		pixel_x;
	int		pixel_y;
	char	tile;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			pixel_x = MINIMAP_X_OFFSET + (x * MINIMAP_SCALE);
			pixel_y = MINIMAP_Y_OFFSET + (y * MINIMAP_SCALE);
			tile = game->map->grid[y][x];
			if (tile == '1')
				draw_square(game, pixel_x, pixel_y, WALL_COLOR);
			else if (tile == '0')
				draw_square(game, pixel_x, pixel_y, FLOOR_COLOR);
			else if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
				draw_square(game, pixel_x, pixel_y, EMPTY_COLOR);
			x++;
		}
		y++;
	}
}

void	render_player_position(t_game *game)
{
	t_circle_params	circle_params;

	circle_params.cx = MINIMAP_X_OFFSET + (int)(game->player->pos->x \
		* MINIMAP_SCALE);
	circle_params.cy = MINIMAP_Y_OFFSET + (int)(game->player->pos->y \
		* MINIMAP_SCALE);
	clamp_to_minimap(&circle_params.cx, &circle_params.cy, game);
	circle_params.radius = PLAYER_RADIUS;
	circle_params.color = PLAYER_COLOR;
	draw_circle(game, &circle_params);
}

void	render_player_direction(t_game *game)
{
	t_line_params	params;

	params.x0 = MINIMAP_X_OFFSET + (int)(game->player->pos->x * MINIMAP_SCALE);
	params.y0 = MINIMAP_Y_OFFSET + (int)(game->player->pos->y * MINIMAP_SCALE);
	normalize_direction(game);
	params.x1 = params.x0 + (int)(game->player->dir->x * RAY_LENGTH);
	params.y1 = params.y0 + (int)(game->player->dir->y * RAY_LENGTH);
	clamp_to_minimap(&params.x1, &params.y1, game);
	draw_line(game, &params, RAY_COLOR);
}

void	*render_minimap(t_game *game)
{
	if (!game || !game->map || !game->map->height || !game->map->width)
		return (NULL) ;
	render_map_tiles(game);
	render_player_position(game);
	render_player_direction(game);
	return (game);
}
