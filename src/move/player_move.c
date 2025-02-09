#include "../../include/cub3d.h"

int	key_hook(int keycode, t_game *game)
{
	game->key_st[keycode] = 1;
	if (keycode == XK_Escape)
		exit(0);
	return (0);
}

int key_release_hook(int keycode, t_game *game)
{
	game->key_st[keycode] = 0;
	return (0);
}

void	strafe_player(t_game *game, int dir, double delta_time)
{
	t_player	*player;
	double		strafeSpeed;
	
	player = game->player;
	strafeSpeed = MOVE_SPEED * delta_time * dir;
	player->pos->x += player->plane->x * strafeSpeed;
	player->pos->y += player->plane->y * strafeSpeed;
	if (game->map->grid[(int)player->pos->y][(int)player->pos->x] == WALL)
	{
		player->pos->x -= player->plane->x * strafeSpeed;
		player->pos->y -= player->plane->y * strafeSpeed;
	}
}

void	rotate_player(t_player *p, int dir, double delta_time)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = p->dir->x;
	oldPlaneX = p->plane->x;
	p->dir->x = p->dir->x * cos(ROT_SPEED * delta_time * dir) - p->dir->y * sin(ROT_SPEED * delta_time * dir);
	p->dir->y = oldDirX * sin(ROT_SPEED * delta_time * dir) + p->dir->y * cos(ROT_SPEED * delta_time * dir);
	p->plane->x = p->plane->x * cos(ROT_SPEED * delta_time * dir) - p->plane->y * sin(ROT_SPEED * delta_time * dir);
	p->plane->y = oldPlaneX * sin(ROT_SPEED * delta_time * dir) + p->plane->y * cos(ROT_SPEED * delta_time * dir);
}

void move_player(t_game *game, int dir, double delta_time)
{
	double	moveSpeed;
	double	newX;
	double	newY;

	moveSpeed = MOVE_SPEED * delta_time;
	newX = game->player->pos->x + game->player->dir->x * moveSpeed * dir;
	newY = game->player->pos->y + game->player->dir->y * moveSpeed * dir;
	if (game->map->grid[(int)newX][(int)newY] == WALL)
	{
		newX = game->player->pos->x - game->player->dir->x * moveSpeed * dir;
		newY = game->player->pos->y -game->player->dir->y * moveSpeed * dir;
	}
	game->player->pos->x = newX;
	game->player->pos->y = newY;
	printf("player x: %lf, player y: %lf\n", game->player->pos->x, game->player->pos->y);
}
