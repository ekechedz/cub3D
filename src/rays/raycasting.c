/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:17:04 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/13 16:17:06 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	initialize_ray(t_game *game, t_ray *ray, double cameraX)
{
	ray->dirX = game->player->dir->x + game->player->plane->x * cameraX;
	ray->dirY = game->player->dir->y + game->player->plane->y * cameraX;
	ray->deltaDistX = fabs(1.0 / ray->dirX);
	ray->deltaDistY = fabs(1.0 / ray->dirY);
	ray->hit = init_vector(ray->posX, ray->posY);
	if (ray->dirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (ray->posX - (int)ray->posX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = ((int)ray->posX + 1.0 - ray->posX) * ray->deltaDistX;
	}
	if (ray->dirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (ray->posY - (int)ray->posY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = ((int)ray->posY + 1.0 - ray->posY) * ray->deltaDistY;
	}
}

int	perform_dda(t_game *game, t_ray *ray, int hitx, int hity)
{
	while (1)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			hitx += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			hity += ray->stepY;
			ray->side = 1;
		}
		if (hity < 0 || hitx >= game->map->width || hitx < 0 || \
			hity >= game->map->height)
			return (0);
		if (game->map->grid[hity][hitx] == WALL)
			break ;
	}
	ray->hit->x = hitx;
	ray->hit->y = hity;
	return (1);
}

t_ray	*cast_rays(t_game *game)
{
	int		x;
	t_ray	*ray;
	double	camerax;

	x = 0;
	ray = init_ray(game->player->pos->x, game->player->pos->y);
	while (x < WIN_WIDTH)
	{
		camerax = 2 * x / (double)WIN_WIDTH - 1;
		initialize_ray(game, ray, camerax);
		if (perform_dda(game, ray, game->player->pos->x, game->player->pos->y))
			render_texture(game, ray, x);
		x ++;
	}
	return (ray);
}

int	main_loop(t_game *game)
{
	struct timeval	current_time;
	double			delta_time;

	gettimeofday(&current_time, NULL);
	delta_time = (current_time.tv_sec - game->last_time.tv_sec) + \
	(current_time.tv_usec - game->last_time.tv_usec) / 1000000.0;
	game->last_time = current_time;
	if (game->key_st[XK_W] || game->key_st[XK_w])
		move_player(game, 1, delta_time);
	if (game->key_st[XK_S] || game->key_st[XK_s])
		move_player(game, -1, delta_time);
	if (game->key_st[XK_A] || game->key_st[XK_a])
		strafe_player(game, -1, delta_time);
	if (game->key_st[XK_D] || game->key_st[XK_d])
		strafe_player(game, 1, delta_time);
	if (game->key_st[XK_Left])
		rotate_player(game->player, -1, delta_time);
	if (game->key_st[XK_Right])
		rotate_player(game->player, 1, delta_time);
	render(game);
	return (0);
}
