/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:35:42 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/13 14:35:44 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_player	*init_player(double x, double y)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos = init_vector(y + 0.5, x + 0.5);
	if (!player->pos)
		return (free_player(player));
	return (player);
}

t_map	*init_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->grid = (char **)malloc(sizeof(char *));
	if (map->grid == NULL)
		return (free_map(map));
	return (map);
}

t_textures	*init_textures(t_config	*config)
{
	t_textures	*t;

	t = malloc(sizeof(t_textures));
	if (!t)
		return (NULL);
	t->north = init_t_image();
	t->east = init_t_image();
	t->south = init_t_image();
	t->west = init_t_image();
	t->floor = init_t_image();
	t->ceiling = init_t_image();
	if (!t->north || !t->east || !t->south || !t->west \
		|| !t->floor || !t->ceiling)
		return (cleanup_all(NULL, config));
	return (t);
}

t_config	*init_config(void)
{
	t_config	*config;

	config = (t_config *)malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	config->map = init_map();
	if (!config->map)
		return (free_config(config));
	config->textures = init_textures(config);
	if (!config->textures)
		return (free_config(config));
	config->ceiling_color = malloc(3 * sizeof(int));
	if (!config->ceiling_color)
		return (free_config(config));
	config->floor_color = malloc(3 * sizeof(int));
	if (!config->floor_color)
		return (free_config(config));
	return (config);
}
