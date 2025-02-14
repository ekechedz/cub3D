/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:35:49 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/14 16:03:45 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/cub3d.h"

t_image	*init_t_image(void)
{
	t_image	*new;

	new = malloc(sizeof(t_image));
	if (!new)
		return (NULL);
	new->img_ptr = NULL;
	new->buff = NULL;
	new->lstsize = 0;
	new->width = 0;
	new->height = 0;
	return (new);
}

t_vector	*init_vector(double x, double y)
{
	t_vector	*vector;

	vector = (t_vector *)malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	return (vector);
}

void	*init_pos_dir_plane(t_player *player, char NSEW)
{
	if (NSEW == 'E')
	{
		player->dir = init_vector(1.0, 0.0);
		player->plane = init_vector(0.0, 0.66);
	}
	else if (NSEW == 'W')
	{
		player->dir = init_vector(-1.0, 0.0);
		player->plane = init_vector(0.0, -0.66);
	}
	else if (NSEW == 'N')
	{
		player->dir = init_vector(0.0, -1.0);
		player->plane = init_vector(0.66, 0.0);
	}
	else if (NSEW == 'S')
	{
		player->dir = init_vector(0.0, 1.0);
		player->plane = init_vector(-0.66, 0.0);
	}
	else
		return (free_player(player));
	if (!player->dir || !player->plane)
		return (free_player(player));
	return (player);
}

t_game	*init_game(t_config *config)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		error("Failure\n", 0, game, config);
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img)
		error("Failure\n", 0, game, config);
	game->screen_data = (int *)mlx_get_data_addr(game->img, &game->bpp, \
		&game->line_length, &game->endian);
	if (!game->screen_data)
		error("Failure\n", 0, game, config);
	game->player = config->player;
	game->map = config->map;
	game->textures = config->textures;
	game->floor_color = config->floor_color;
	game->ceiling_color = config->ceiling_color;
	game->config = config;
	return (game);
}

t_ray	*init_ray(double x, double y)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->posX = x;
	ray->posY = y;
	ray->dist = 0.0;
	ray->hit = NULL;
	ray->side = 0;
	ray->lineHeight = 0.0;
	return (ray);
}
