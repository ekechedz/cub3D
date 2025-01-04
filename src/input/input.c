#include "../../include/cub3d.h"

void handle_input(int key, t_game *game)
{
    if (key == 65307)
    { // ESC key
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
}

int handle_input_wrapper(int key, void *param)
{
    handle_input(key, (t_game *)param); // Call your actual function
    return (0);                         // Return an int as expected
}
