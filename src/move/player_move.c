#include "../../include/cub3d.h"

// Key press handler
int key_hook(int keycode, t_game *game)
{
    game->key_state[keycode] = 1;  // Mark the key as pressed

    if (keycode == 65307) {  // ESC key
        exit(0);  // Close the game
    }

    return (0);
}

// Key release handler
int key_release_hook(int keycode, t_game *game)
{
    game->key_state[keycode] = 0;  // Mark the key as released
    return (0);
}


void strafe_player(t_game *game, int direction, double delta_time)
{
    t_player *player = game->player;

    double strafeSpeed = MOVE_SPEED * delta_time * direction; // Adjust speed with delta time
    player->pos->x += player->plane->x * strafeSpeed;
    player->pos->y += player->plane->y * strafeSpeed;

    // Boundary check
    if (game->map->grid[(int)player->pos->y][(int)player->pos->x] == WALL)
    {
        player->pos->x -= player->plane->x * strafeSpeed;
        player->pos->y -= player->plane->y * strafeSpeed;
    }
}

void rotate_player(t_game *game, int direction, double delta_time)
{
    t_player *player = game->player;
    double oldDirX = player->dir->x;
    double oldPlaneX = player->plane->x;

    // Rotate the player's direction and plane vectors
    player->dir->x = player->dir->x * cos(ROT_SPEED * delta_time * direction) - player->dir->y * sin(ROT_SPEED * delta_time * direction);
    player->dir->y = oldDirX * sin(ROT_SPEED * delta_time * direction) + player->dir->y * cos(ROT_SPEED * delta_time * direction);
    player->plane->x = player->plane->x * cos(ROT_SPEED * delta_time * direction) - player->plane->y * sin(ROT_SPEED * delta_time * direction);
    player->plane->y = oldPlaneX * sin(ROT_SPEED * delta_time * direction) + player->plane->y * cos(ROT_SPEED * delta_time * direction);
}

void move_player(t_game *game, int direction, double delta_time)
{
	t_player *player = game->player;

	double moveSpeed = MOVE_SPEED * delta_time; // Adjust speed based on delta time
	player->pos->x += player->dir->x * moveSpeed * direction;
	player->pos->y += player->dir->y * moveSpeed * direction;

	// Boundary check (same as before)
	if (game->map->grid[(int)player->pos->y][(int)player->pos->x] == WALL)
	{
		player->pos->x -= player->dir->x * moveSpeed * direction;
		player->pos->y -= player->dir->y * moveSpeed * direction;
	}
}
