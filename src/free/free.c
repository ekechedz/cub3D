/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:38:55 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/14 16:36:36 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/cub3d.h"

void free_image(t_image *img, void *mlx)
{
	if (img)
	{
		if (img->img_ptr)
			mlx_destroy_image(mlx, img->img_ptr);
		// if (img->buff)
		// 	free(img->buff);
		free(img);
	}
}

t_textures *free_textures(t_textures *t, void *mlx)
{
	if (t && mlx)
	{
		free_image(t->north, mlx);
		free_image(t->south, mlx);
		free_image(t->east, mlx);
		free_image(t->west, mlx);
		free_image(t->floor, mlx);
		free_image(t->ceiling, mlx);
		free(t);
	}
	return (NULL);
}

void	*free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map && !map->height)
		return NULL;
	while (i < map->height)
	{
		free(map->grid[i]);
		i ++;
	}
	free(map->grid);
	free(map);
	map = NULL;
	return (NULL);
}

void	*free_config(t_config *config)
{
	if (!config)
		return (NULL);
	if (config->map)
		free_map(config->map);
	// if (config->textures)
	// 	free_textures(config->textures, NULL);
	if (config->floor_color)
		free (config->floor_color);
	if (config->ceiling_color)
		free (config->ceiling_color);
	if (config->player)
		free_player(config->player);
	free_used_keys((char **)config->used_keys);
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
	// if (game->player)
	// 	free_player(game->player);
	// if (game->map)
	// 	free_map(game->map);
	// if (game->floor_color)
	// 	free(game->floor_color);
	// if (game->ceiling_color)
	// 	free(game->ceiling_color);
	if (game->textures)
		free_textures(game->textures, game->mlx);
	// if (game->screen_data)
	// 	free(game->screen_data); //maybe theres an mlx function
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

int	cleanup_all(t_game	*game, t_config *config)
{
	if (game)
		free_game(game);
	if (config)
		free_config(config);
	exit(1);
}

void	free_used_keys(char **used_keys)
{
	int	i;
	i = 0;
	if (!used_keys)
		return;
	while (i < MAX_KEYS)
	{
		if (used_keys[i])
		{
			free(used_keys[i]);
			used_keys[i] = NULL;
		}
		i++;
	}
	//free(used_keys);
}
