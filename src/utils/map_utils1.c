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
