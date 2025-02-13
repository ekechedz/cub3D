#include "../../include/cub3d.h"

void	init_events(t_game *game)
{
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game->win)
	{
		write(2, "Window creation failed\n", 23);
		free_game(game);
		return;
	}
	mlx_clear_window(game->mlx, game->win);
	memset(game->key_st, 0, sizeof(game->key_st)); //maybe in init_game is better
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_hook(game->win, 3, 1L << 1, key_release_hook, game);
	mlx_loop_hook(game->mlx, main_loop, game);
	//mlx_loop_hook(game->mlx, handle_close, game); a ver
}

int	handle_key_press(int keycode, t_game *game) //is it used
{
	if (keycode == XK_Escape)
		mlx_loop_end(game->mlx);
	return 0;
}

int	handle_close(t_game *game) //is it used
{
	mlx_loop_end(game->mlx);
	return (0);
}

int	close_window(void *param) //is it used at all
{
	mlx_destroy_window(param, param);
	exit(0);
	return (0);
}
