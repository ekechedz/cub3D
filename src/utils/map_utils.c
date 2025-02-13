/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:42:59 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/13 14:43:02 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	calculate_line_parameters(t_line_params *params)
{
	params->dx = abs(params->x1 - params->x0);
	params->dy = abs(params->y1 - params->y0);
	if (params->x0 < params->x1)
		params->sx = 1;
	else
		params->sx = -1;
	if (params->y0 < params->y1)
		params->sy = 1;
	else
		params->sy = -1;
	params->err = params->dx - params->dy;
}

void	update_line_coordinates(int *x0, int *y0, t_line_params *params)
{
	int	e2;

	e2 = params->err * 2;
	if (e2 > -params->dy)
	{
		params->err -= params->dy;
		*x0 += params->sx;
	}
	if (e2 < params->dx)
	{
		params->err += params->dx;
		*y0 += params->sy;
	}
}

void	draw_line(t_game *game, t_line_params *params, int color)
{
	calculate_line_parameters(params);
	while (1)
	{
		if (params->x0 >= 0 && params->x0 < WIN_WIDTH \
			&& params->y0 >= 0 && params->y0 < WIN_HEIGHT)
			game->screen_data[params->y0 * WIN_WIDTH + params->x0] = color;
		if (check_for_wall_collision(game, params->x0, params->y0))
			break ;
		update_line_coordinates(&params->x0, &params->y0, params);
		if (params->x0 == params->x1 && params->y0 == params->y1)
			break ;
	}
}

void	draw_circle(t_game *game, t_circle_params *params)
{
	int	x;
	int	y;
	int	pixel_x;
	int	pixel_y;

	y = -params->radius;
	while (y <= params->radius)
	{
		x = -params->radius;
		while (x <= params->radius)
		{
			if (x * x + y * y <= params->radius * params->radius)
			{
				pixel_x = params->cx + x;
				pixel_y = params->cy + y;
				if (pixel_x >= 0 && pixel_x < WIN_WIDTH && pixel_y >= 0 \
					&& pixel_y < WIN_HEIGHT)
					game->screen_data[pixel_y * WIN_WIDTH \
						+ pixel_x] = params->color;
			}
			x++;
		}
		y++;
	}
}

void	normalize_direction(t_game *game)
{
	float	length;

	length = sqrt(game->player->dir->x * game->player->dir->x \
		+ game->player->dir->y * game->player->dir->y);
	if (length > 0)
	{
		game->player->dir->x /= length;
		game->player->dir->y /= length;
	}
}
