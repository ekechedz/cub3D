#include "../../include/cub3d.h"

void strafe_player(t_game *game, int direction)
{
	t_player *player = game->player;

	// Move left or right by using the player's plane vector
	double strafeSpeed = MOVE_SPEED * direction;
	player->pos->x += player->plane->x * strafeSpeed;
	player->pos->y += player->plane->y * strafeSpeed;

	// Boundary check (same as for forward/backward)
	if (game->map->grid[(int)player->pos->y][(int)player->pos->x] == WALL)
	{
		player->pos->x -= player->plane->x * strafeSpeed;
		player->pos->y -= player->plane->y * strafeSpeed;
	}
}
void rotate_player(t_game *game, int direction)
{
	t_player *player = game->player;
	double oldDirX = player->dir->x;
	double oldPlaneX = player->plane->x;

	// Rotate the player's direction and plane vectors
	player->dir->x = player->dir->x * cos(ROT_SPEED * direction) - player->dir->y * sin(ROT_SPEED * direction);
	player->dir->y = oldDirX * sin(ROT_SPEED * direction) + player->dir->y * cos(ROT_SPEED * direction);
	player->plane->x = player->plane->x * cos(ROT_SPEED * direction) - player->plane->y * sin(ROT_SPEED * direction);
	player->plane->y = oldPlaneX * sin(ROT_SPEED * direction) + player->plane->y * cos(ROT_SPEED * direction);
}

void move_player(t_game *game, int direction)
{
	t_player *player = game->player;

	// Forward/backward movement: move along the direction vector
	double moveSpeed = MOVE_SPEED * direction;
	player->pos->x += player->dir->x * moveSpeed;
	player->pos->y += player->dir->y * moveSpeed;

	// Add boundary checks (if your game grid has walls)
	if (game->map->grid[(int)player->pos->y][(int)player->pos->x] == WALL)
	{
		player->pos->x -= player->dir->x * moveSpeed;
		player->pos->y -= player->dir->y * moveSpeed;
	}
}

int key_hook(int keycode, t_game *game)
{
	// Player movement keys
	if (keycode == 65307)		 // ESC key
		exit(0);				 // Close the game
	if (keycode == 119)			 // W key (move forward)
		move_player(game, 1);	 // move forward
	if (keycode == 115)			 // S key (move backward)
		move_player(game, -1);	 // move backward
	if (keycode == 97)			 // A key (move left)
		strafe_player(game, -1); // move left
	if (keycode == 100)			 // D key (move right)
		strafe_player(game, 1);	 // move right
	if (keycode == 65361)		 // Left arrow (rotate left)
		rotate_player(game, -1); // rotate left
	if (keycode == 65363)		 // Right arrow (rotate right)
		rotate_player(game, 1);	 // rotate right

	//render_minimap(game->mlx, game->win, game->config);
	render(game);
	return (0);
}

//for the player movment
// Update player direction based on keyboard input (e.g., 'W', 'S' for movement)
// void handle_input(t_game *game) {
//     if (key_pressed(W_KEY)) {
//         game->player->pos->x += game->player->dir->x * MOVE_SPEED;
//         game->player->pos->y += game->player->dir->y * MOVE_SPEED;
//     }
//     if (key_pressed(S_KEY)) {
//         game->player->pos->x -= game->player->dir->x * MOVE_SPEED;
//         game->player->pos->y -= game->player->dir->y * MOVE_SPEED;
//     }

//     // Rotation handling for left/right (e.g., 'A', 'D' keys)
//     if (key_pressed(LEFT_KEY)) {
//         // Rotate the player to the left
//         double oldDirX = game->player->dir->x;
//         game->player->dir->x = game->player->dir->x * cos(-ROT_SPEED) - game->player->dir->y * sin(-ROT_SPEED);
//         game->player->dir->y = oldDirX * sin(-ROT_SPEED) + game->player->dir->y * cos(-ROT_SPEED);
//     }
//     if (key_pressed(RIGHT_KEY)) {
//         // Rotate the player to the right
//         double oldDirX = game->player->dir->x;
//         game->player->dir->x = game->player->dir->x * cos(ROT_SPEED) - game->player->dir->y * sin(ROT_SPEED);
//         game->player->dir->y = oldDirX * sin(ROT_SPEED) + game->player->dir->y * cos(ROT_SPEED);
//     }
// }
