#include "../../include/cub3d.h"

#define MINIMAP_SCALE 10	// Scale for minimap (1 map unit = 10 pixels)
#define MINIMAP_X_OFFSET 20 // Minimap position on screen
#define MINIMAP_Y_OFFSET 20
#define PLAYER_COLOR 0xFF4500 // Red dot for player
#define WALL_COLOR 0x444444
#define FLOOR_COLOR 0x222222
#define EMPTY_COLOR 0x888888
#define RAY_COLOR 0x00FFAA // Yellow for view direction
#define PLAYER_RADIUS 3	   // Player indicator radius
#define RAY_LENGTH 100	   // Player's view ray length

int apply_shading(int i, int j, int color)
{
	if (i == 0 || j == 0 || i == MINIMAP_SCALE - 1 || j == MINIMAP_SCALE - 1)
		return color / 2;
	else
		return color;
}

void draw_square(t_game *game, int x, int y, int color)
{
	int i;
	int j;
	int pixel_x;
	int pixel_y;
	int shade;

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

void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	int dx, dy, sx, sy, err, e2;
	int map_x, map_y;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1)
	{
		if (x0 >= 0 && x0 < WIN_WIDTH && y0 >= 0 && y0 < WIN_HEIGHT)
			game->screen_data[y0 * WIN_WIDTH + x0] = color;

		map_x = (x0 - MINIMAP_X_OFFSET) / MINIMAP_SCALE;
		map_y = (y0 - MINIMAP_Y_OFFSET) / MINIMAP_SCALE;
		if (map_x >= 0 && map_x < game->map->width &&
			map_y >= 0 && map_y < game->map->height &&
			game->map->grid[map_y][map_x] == '1')
			break;
		if (x0 == x1 && y0 == y1)
			break;
		e2 = err * 2;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void draw_circle(t_game *game, int cx, int cy, int radius, int color)
{
	int x;
	int y;
	int pixel_x;
	int pixel_y;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				pixel_x = cx + x;
				pixel_y = cy + y;
				if (pixel_x >= 0 && pixel_x < WIN_WIDTH && pixel_y >= 0 && pixel_y < WIN_HEIGHT)
					game->screen_data[pixel_y * WIN_WIDTH + pixel_x] = color;
			}
			x++;
		}
		y++;
	}
}

// Normalize the player's direction vector
void normalize_direction(t_game *game)
{
	float length;

	length = sqrt(game->player->dir->x * game->player->dir->x +
				  game->player->dir->y * game->player->dir->y);
	if (length > 0)
	{
		game->player->dir->x /= length;
		game->player->dir->y /= length;
	}
}

void clamp_to_minimap(int *x, int *y, t_game *game)
{
	int min_x;
	int min_y;
	int max_x;
	int max_y;

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

void render_map_tiles(t_game *game)
{
	int x;
	int y;
	int pixel_x;
	int pixel_y;
	char tile;

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

void render_player_position(t_game *game)
{
	int player_x;
	int player_y;

	player_x = MINIMAP_X_OFFSET + (int)(game->player->pos->x * MINIMAP_SCALE);
	player_y = MINIMAP_Y_OFFSET + (int)(game->player->pos->y * MINIMAP_SCALE);
	clamp_to_minimap(&player_x, &player_y, game);
	draw_circle(game, player_x, player_y, PLAYER_RADIUS, PLAYER_COLOR);
}
void render_player_direction(t_game *game)
{
	int player_x;
	int player_y;
	int end_x;
	int end_y;

	player_x = MINIMAP_X_OFFSET + (int)(game->player->pos->x * MINIMAP_SCALE);
	player_y = MINIMAP_Y_OFFSET + (int)(game->player->pos->y * MINIMAP_SCALE);
	normalize_direction(game);
	end_x = player_x + (int)(game->player->dir->x * RAY_LENGTH);
	end_y = player_y + (int)(game->player->dir->y * RAY_LENGTH);
	clamp_to_minimap(&end_x, &end_y, game);
	draw_line(game, player_x, player_y, end_x, end_y, RAY_COLOR);
}

void render_minimap(t_game *game)
{
	render_map_tiles(game);
	render_player_position(game);
	render_player_direction(game);
}
