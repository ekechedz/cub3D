#include "../../include/cub3d.h"

void render_frame(t_game *game)
{
	// Clear the window
	mlx_clear_window(game->mlx, game->win);

	// Draw a simple placeholder frame
	mlx_string_put(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2, 0xFFFFFF, "Rendering...");

	// Temporary: Display map dimensions in the console
	printf("Rendering frame with map size: %dx%d\n", game->map->width, game->map->height);
}

int render_frame_wrapper(void *param)
{
	render_frame((t_game *)param); // Call your actual function
	return (0);					   // Return an int as expected
}
