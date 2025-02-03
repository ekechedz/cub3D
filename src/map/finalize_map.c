#include "../../include/cub3d.h"

void finalize_map(t_config *config)
{
	int x, y;

	// Ensure map is valid
	if (!config->map || !config->map->grid)
		exit_with_error("Map is missing or incomplete", 1);

	// Validate map boundaries (surrounded by walls)
	for (y = 0; y < config->map->height; y++)
	{
		for (x = 0; x < config->map->width; x++)
		{
			if (config->map->grid[y][x] == '0' || config->map->grid[y][x] == 'N' ||
				config->map->grid[y][x] == 'S' || config->map->grid[y][x] == 'E' || config->map->grid[y][x] == 'W')
			{
				if (x == 0 || y == 0 || y == config->map->height - 1 || x == config->map->width - 1)
					exit_with_error("Map is not properly enclosed by walls", 1);

				// Check for open spaces around tiles
				if (config->map->grid[y - 1][x] == ' ' || config->map->grid[y + 1][x] == ' ' ||
					config->map->grid[y][x - 1] == ' ' || config->map->grid[y][x + 1] == ' ')
					exit_with_error("Map contains open spaces near walls", 1);
			}
		}
	}

	// Validate player start position
	int player_count = 0;
	for (y = 0; y < config->map->height; y++)
	{
		for (x = 0; x < config->map->width; x++)
		{
			if (config->map->grid[y][x] == 'N' || config->map->grid[y][x] == 'S' ||
				config->map->grid[y][x] == 'E' || config->map->grid[y][x] == 'W')
			{
				player_count++;

				// Set player's initial position
				config->player->pos->x = x + 0.5;
				config->player->pos->y = y + 0.5;

				// Set player's initial direction based on map character
				if (config->map->grid[y][x] == 'N')
				{
					config->player->dir->x = 0;
					config->player->dir->y = -1;
				}
				else if (config->map->grid[y][x] == 'S')
				{
					config->player->dir->x = 0;
					config->player->dir->y = 1;
				}
				else if (config->map->grid[y][x] == 'E')
				{
					config->player->dir->x = 1;
					config->player->dir->y = 0;
				}
				else if (config->map->grid[y][x] == 'W')
				{
					config->player->dir->x = -1;
					config->player->dir->y = 0;
				}

				// Replace player's starting position in the map with '0'
				//config->map->grid[y][x] = '0';
			}
		}
	}
	printf("%d\n",player_count);
	if (player_count != 1)
		exit_with_error("Map must contain exactly one player start position", 1);
}
