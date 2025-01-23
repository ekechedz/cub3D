#include "../../include/cub3d.h"

void init_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        perror("Error initializing MiniLibX");
        exit(1);
    }

    game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
    if (!game->win)
    {
        perror("Error creating window");
        exit(1);
    }

    game->floor_color = 0x00AA00;   // Green
    game->ceiling_color = 0x0000FF; // Blue
}
