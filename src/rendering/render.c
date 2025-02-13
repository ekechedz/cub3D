/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:14:04 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/13 17:32:47 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static double	set_draw_info(t_ray *ray, double dist);
static int		render_slice(t_ray *ray, int texx, int x, t_game *game);

void	*render(t_game *game)
{
	ft_memset(game->screen_data, 0, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
	if (!cast_rays(game))
		return (NULL);
	if (!render_minimap(game))
		return (NULL);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (game);
}

static double	set_draw_info(t_ray *ray, double dist)
{
	double	wallx;

	ray->lineHeight = (int)(WIN_HEIGHT / dist);
	ray->drawStart = -ray->lineHeight / 2 + WIN_HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + WIN_HEIGHT / 2;
	if (ray->drawEnd >= WIN_HEIGHT)
		ray->drawEnd = WIN_HEIGHT;
	if (ray->side == 0)
		wallx = (ray->posY + dist * ray->dirY);
	else
		wallx = (ray->posX + dist * ray->dirX);
	wallx -= floor(wallx);
	return (wallx);
}

void	render_texture(t_game *game, t_ray *ray, int x)
{
	int		texx;
	double	dist;
	double	wallx;

	if (ray->side == 0)
		dist = (ray->hit->x - ray->posX + (1 - ray->stepX) / 2) / ray->dirX;
	else
		dist = (ray->hit->y - ray->posY + (1 - ray->stepY) / 2) / ray->dirY;
	if (dist <= 0)
		dist = 0.1;
	wallx = set_draw_info(ray, dist);
	texx = (int)(wallx * (double)TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->dirX < 0) || (ray->side == 1 && ray->dirY > 0))
		texx = TEXTURE_WIDTH - texx - 1;
	render_slice(ray, texx, x, game);
}

static int	render_slice(t_ray *ray, int texx, int x, t_game *game)
{
	int		y;
	int		texy;
	int		color;
	t_image	*texture;

	y = 0;
	texture = choose_texture(ray, game);
	while (y++ < ray->drawStart)
		game->screen_data[y * WIN_WIDTH + x] = *game->ceiling_color;
	while (y < ray->drawEnd)
	{
		texy = (((y - WIN_HEIGHT / 2 + ray->lineHeight / 2) * TEXTURE_HEIGHT) \
		/ ray->lineHeight);
		if (texy < 0)
			texy = 0;
		if (texy >= TEXTURE_HEIGHT)
			texy = TEXTURE_HEIGHT - 1;
		color = get_txt_color(texture, texx, texy);
		game->screen_data[y * WIN_WIDTH + x] = color;
		y ++;
	}
	while (y++ < WIN_HEIGHT)
		game->screen_data[y * WIN_WIDTH + x] = *game->floor_color;
	return (0);
}
