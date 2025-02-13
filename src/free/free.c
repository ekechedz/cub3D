#include "../../include/cub3d.h"

t_textures	*free_textures(t_textures *t)
{
	if (t->north)
		free (t->north);
	if (t->south)
		free (t->south);
	if (t->east)
		free (t->east);
	if (t->west)
		free (t->west);
	if (t->floor)
		free (t->floor);
	if (t->ceiling)
		free (t->ceiling);
	free (t);
	return (NULL);
}

void	*free_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i ++;
	}
	free(map->grid);
	free(map);
	return (NULL);
}

void	*free_config(t_config *config)
{
	if (config->map)
		free_map(config->map);
	if (config->textures)
		free_textures(config->textures);
	if (config->floor_color)
		free (config->floor_color);
	if (config->ceiling_color)
		free (config->ceiling_color);
	if (config->player)
		free_player(config->player); //not implemented
	free (config);
	return (NULL);
}

void	*free_player(t_player *player)
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
	}
	return (NULL);
}

void	*free_game(t_game *game)
{
	if (game->player)
		free_player(game->player);
	if (game->map)
		free_map(game->map);
	if (game->floor_color)
		free(game->floor_color);
	if (game->ceiling_color)
		free(game->ceiling_color);
	if (game->textures)
		free_textures(game->textures);
	if (game->screen_data)
		free(game->screen_data); //maybe theres an mlx function
	if (game->img)
		mlx_destroy_image(game->mlx, game->img); //do i have to free it still?
	if (game->win)
		mlx_destroy_window(game->mlx, game->win); //same
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free (game);
	return (NULL);
}

void	*cleanup_all(t_game	*game, t_config *config)
{
	if (game)
		free_game(game);
	if (config)
		free_config(config);
	return (NULL);
}
