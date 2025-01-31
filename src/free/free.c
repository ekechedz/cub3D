#include "../../include/cub3d.h"

void free_config(t_config *config)
{
	if (!config)
		return;

	if (config->map)
	{
		for (int i = 0; i < config->map->height; i++)
			free(config->map->grid[i]);
		free(config->map->grid);
		free(config->map);
	}

	free(config->textures->north->buff);
	free(config->textures->south->buff);
	free(config->textures->west->buff);
	free(config->textures->east->buff);

	free(config);
}

void free_game(t_game *game)
{
	if (!game)
		return;

	if (game->win)
		mlx_destroy_window(game->mlx, game->win);

	if (game->mlx)
		free(game->mlx); // Only free if mlx was successfully initialized

	free_config(game->config);
	free(game);
}

int	free_player(t_player *player)
{
	if (player)
	{
		if (player->dir)
			free(player->dir);
		if (player->plane)
			free(player->plane);
		if (player->pos)
			free(player->pos);
		free(player);
		return (0);
	}
	return (1);
}