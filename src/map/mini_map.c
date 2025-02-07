#include "../../include/cub3d.h"
#include <math.h>

#define FOV_ANGLE M_PI / 3 // 60-degree field of view
#define NUM_RAYS 10        // Number of rays to cast for FOV
#define RAY_LENGTH 100     // Max distance of vision

void cast_ray(void *mlx, void *win, t_config *config, double angle, int player_x, int player_y, int fov_color)
{
    double ray_x = player_x;
    double ray_y = player_y;
    double step_size = 1.0; // Small steps to check collisions

    while (1)
    {
        int map_x = (int)(ray_x / (TILE_SIZE * MINI_MAP_SCALE));
        int map_y = (int)(ray_y / (TILE_SIZE * MINI_MAP_SCALE));

        // Check if ray has hit a wall
        if (config->map->grid[map_y][map_x] == '1')
            break;

        // Draw the ray point
        mlx_pixel_put(mlx, win, (int)ray_x, (int)ray_y, fov_color);

        // Move the ray forward
        ray_x += cos(angle) * step_size;
        ray_y -= sin(angle) * step_size; // Invert Y for correct orientation
    }
}

void render_minimap(void *mlx, void *win, t_config *config)
{
    if (!config->map || !config->map->grid)
    {
        printf("Map is not initialized.\n");
        return;
    }

    int wall_color = 0xFF0000;    // Red for walls
    int floor_color = 0x00FF00;   // Green for empty spaces
    int player_color = 0x0000FF;  // Blue for player
    int fov_color = 0xFFFF00;     // Yellow for FOV lines

    int player_x = config->player->pos->x, player_y = 0;
    double player_angle = 0;

    // Iterate over each tile in the map
    for (int y = 0; y < config->map->height; y++)
    {
        for (int x = 0; x < config->map->width; x++)
        {
            char tile = config->map->grid[y][x];
            int screen_x = x * TILE_SIZE * MINI_MAP_SCALE;
            int screen_y = y * TILE_SIZE * MINI_MAP_SCALE;
            int screen_size = TILE_SIZE * MINI_MAP_SCALE;

            if (tile == '1') // Wall
                mlx_pixel_put(mlx, win, screen_x, screen_y, wall_color);
            else if (tile == '0') // Floor
                mlx_pixel_put(mlx, win, screen_x, screen_y, floor_color);
            else if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W') // Player
            {
                player_x = screen_x + screen_size / 2;
                player_y = screen_y + screen_size / 2;

                // Determine player direction
                if (tile == 'N') player_angle = M_PI / 2;
                if (tile == 'S') player_angle = 3 * M_PI / 2;
                if (tile == 'E') player_angle = 0;
                if (tile == 'W') player_angle = M_PI;

                // Draw player
                for (int px = screen_x + screen_size / 4; px < screen_x + 3 * screen_size / 4; px++)
                {
                    for (int py = screen_y + screen_size / 4; py < screen_y + 3 * screen_size / 4; py++)
                    {
                        mlx_pixel_put(mlx, win, px, py, player_color);
                    }
                }
            }
        }
    }

    // Cast FOV rays
    for (int i = -NUM_RAYS / 2; i < NUM_RAYS / 2; i++)
    {
        double ray_angle = player_angle + (i * (FOV_ANGLE / NUM_RAYS));
        cast_ray(mlx, win, config, ray_angle, player_x, player_y, fov_color);
    }
}
