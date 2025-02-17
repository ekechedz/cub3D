/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:36:04 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/13 15:38:47 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	strafe_player(t_game *game, int dir, double delta_time)
{
	double	strafe_speed;
	double	new_x;
	double	new_y;

	strafe_speed = MOVE_SPEED * delta_time * dir;
	new_x = game->player->pos->x + game->player->plane->x * strafe_speed;
	new_y = game->player->pos->y + game->player->plane->y * strafe_speed;
	if (game->map->grid[(int)new_y][(int)new_x] == WALL)
	{
		new_x = game->player->pos->x - game->player->plane->x * strafe_speed;
		new_y = game->player->pos->y - game->player->plane->y * strafe_speed;
	}
	game->player->pos->x = new_x;
	game->player->pos->y = new_y;
}

void	rotate_player(t_player *p, int dir, double delta_time)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir->x;
	old_plane_x = p->plane->x;
	p->dir->x = p->dir->x * cos(ROT_SPEED * delta_time * dir) \
	- p->dir->y * sin(ROT_SPEED * delta_time * dir);
	p->dir->y = old_dir_x * sin(ROT_SPEED * delta_time * dir) \
	+ p->dir->y * cos(ROT_SPEED * delta_time * dir);
	p->plane->x = p->plane->x * cos(ROT_SPEED * delta_time * dir) \
	- p->plane->y * sin(ROT_SPEED * delta_time * dir);
	p->plane->y = old_plane_x * sin(ROT_SPEED * delta_time * dir) \
	+ p->plane->y * cos(ROT_SPEED * delta_time * dir);
}

void	move_player(t_game *game, int dir, double delta_time)
{
	double	move_speed;
	double	new_x;
	double	new_y;

	move_speed = MOVE_SPEED * delta_time;
	new_x = game->player->pos->x + game->player->dir->x * move_speed * dir;
	new_y = game->player->pos->y + game->player->dir->y * move_speed * dir;
	if (game->map->grid[(int)new_y][(int)new_x] == WALL)
	{
		new_x = game->player->pos->x - game->player->dir->x * move_speed * dir;
		new_y = game->player->pos->y - game->player->dir->y * move_speed * dir;
	}
	game->player->pos->x = new_x;
	game->player->pos->y = new_y;
}
