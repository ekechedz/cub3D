#include "include/cub3d.h"

int main(int argc, char **argv)
{
    t_game game;

    (void)argc;
    (void)argv;
    // if (argc != 2)
    // {
    //     fprintf(stderr, "Usage: %s <map_file.cub>\n", argv[0]);
    //     return 1;
    // }

    // Initialize the game structure
    init_game(&game);

    // Parse the map file
    //parse_map(argv[1], &game);

    // Start the game loop (render and input handling)
    mlx_loop_hook(game.mlx, render_frame_wrapper, &game);
    mlx_key_hook(game.win, handle_input_wrapper, &game);

    // Run the MLX event loop
    mlx_loop(game.mlx);

    // Clean up resources
    //cleanup(&game);

    return 0;
}
