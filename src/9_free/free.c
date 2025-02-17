/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:38:55 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/17 14:17:02 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_image(t_image *img, void *mlx)
{
	if (img)
	{
		if (img->img_ptr)
			mlx_destroy_image(mlx, img->img_ptr);
		if (img->fp)
		{
			free(img->fp);
			img->fp = NULL;
		}
		free(img);
	}
}

t_textures	*free_textures(t_textures *t, void *mlx)
{
	if (t)
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
		return (NULL);
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
	if (config->floor_color)
		free (config->floor_color);
	if (config->ceiling_color)
		free (config->ceiling_color);
	if (config->player)
		free_player(config->player);
	if (config->textures)
		free_textures(config->textures, config->mlx);
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
