/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:17:04 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/17 14:21:21 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	initialize_ray(t_game *game, t_ray *r, double cameraX)
{
	r->dir_x = game->player->dir->x + game->player->plane->x * cameraX;
	r->dir_y = game->player->dir->y + game->player->plane->y * cameraX;
	r->delta_dist_x = fabs(1.0 / r->dir_x);
	r->delta_dist_y = fabs(1.0 / r->dir_y);
	r->hit = init_vector(r->pos_x, r->pos_y);
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (r->pos_x - (int)r->pos_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = ((int)r->pos_x + 1.0 - r->pos_x) * r->delta_dist_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (r->pos_y - (int)r->pos_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = ((int)r->pos_y + 1.0 - r->pos_y) * r->delta_dist_y;
	}
}

int	perform_dda(t_game *game, t_ray *ray, int hitx, int hity)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			hitx += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			hity += ray->step_y;
			ray->side = 1;
		}
		if (hity < 0 || hitx >= game->map->width || hitx < 0 || \
			hity >= game->map->height)
			return (0);
		if (game->map->grid[hity][hitx] == '1')
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
	while (x < WIN_WIDTH)
	{
		ray = init_ray(game->player->pos->x, game->player->pos->y);
		camerax = 2 * x / (double)WIN_WIDTH - 1;
		initialize_ray(game, ray, camerax);
		if (perform_dda(game, ray, game->player->pos->x, game->player->pos->y))
			render_texture(game, ray, x);
		x ++;
		free_ray(ray);
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
	if (!render(game))
		return (1);
	return (0);
}
