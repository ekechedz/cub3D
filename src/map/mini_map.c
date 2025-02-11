#include "../../include/cub3d.h"

#define MINIMAP_SCALE 10  // Scale for minimap (1 map unit = 10 pixels)
#define MINIMAP_X_OFFSET 20  // Minimap position on screen
#define MINIMAP_Y_OFFSET 20
#define PLAYER_COLOR 0xFF0000  // Red dot for player
#define WALL_COLOR 0xFFFFFF    // White walls
#define FLOOR_COLOR 0x000000   // Black for empty space
#define RAY_COLOR 0xFFFF00     // Yellow for view direction

// Draw a small square (used for walls & empty space)
void draw_square(t_game *game, int x, int y, int color)
{
    int i, j;
    for (i = 0; i < MINIMAP_SCALE; i++)
    {
        for (j = 0; j < MINIMAP_SCALE; j++)
        {
            int pixel_x = x + i;
            int pixel_y = y + j;
            if (pixel_x < WIN_WIDTH && pixel_y < WIN_HEIGHT)
                game->screen_data[pixel_y * WIN_WIDTH + pixel_x] = color;
        }
    }
}

// Draw a simple line (Bresenham’s algorithm) for player view
void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1)
    {
        if (x0 >= 0 && x0 < WIN_WIDTH && y0 >= 0 && y0 < WIN_HEIGHT)
            game->screen_data[y0 * WIN_WIDTH + x0] = color;

        int e2 = err * 2;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

// Draw a small circle (used for the player)
void draw_circle(t_game *game, int cx, int cy, int radius, int color)
{
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                int pixel_x = cx + x;
                int pixel_y = cy + y;
                if (pixel_x >= 0 && pixel_x < WIN_WIDTH && pixel_y >= 0 && pixel_y < WIN_HEIGHT)
                    game->screen_data[pixel_y * WIN_WIDTH + pixel_x] = color;
            }
        }
    }
}

// Draw the minimap based on game->map
void render_minimap(t_game *game)
{
	//printf("Rendering minimap for map size: %d x %d\n", game->map->width, game->map->height);
    // Clear minimap area first
    for (int y = 0; y < game->map->height; y++)
    {
        for (int x = 0; x < game->map->width; x++)
        {
            int pixel_x = MINIMAP_X_OFFSET + (x * MINIMAP_SCALE);
            int pixel_y = MINIMAP_Y_OFFSET + ((game->map->height - y) * MINIMAP_SCALE);

            if (game->map->grid[y][x] == '1')  // Walls
                draw_square(game, pixel_x, pixel_y, WALL_COLOR);
            else  // Empty space
                draw_square(game, pixel_x, pixel_y, FLOOR_COLOR);
        }
    }
	//printf("Player position: (%.2f, %.2f)\n", game->player->pos->x, game->player->pos->y);

    // Draw player position on minimap (scaled position)
    int player_x = MINIMAP_X_OFFSET + (int)(game->player->pos->x * MINIMAP_SCALE);
    int player_y = MINIMAP_Y_OFFSET + (int)((game->map->height - game->player->pos->y) * MINIMAP_SCALE);
	//printf("Player minimap position: (%d, %d)\n", player_x, player_y);
    draw_circle(game, player_x, player_y, 3, PLAYER_COLOR);

    // Draw player view direction (ray)
    int end_x = player_x + game->player->dir->x * 10 * MINIMAP_SCALE;
    int end_y = player_y - game->player->dir->y * 10 * MINIMAP_SCALE;
    draw_line(game, player_x, player_y, end_x, end_y, RAY_COLOR);
}
