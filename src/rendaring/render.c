#include "../../include/cub3d.h"

void put_pixel_from_texture(t_game *game, t_image *texture, t_vector tex, t_vector screen)
{
    int color;
    int pixelIndex;
    char *pixelData;

    // Convert screen.x and screen.y to integers
    int screenX = (int)screen.x;
    int screenY = (int)screen.y;

    // Make sure the texture coordinates are within bounds
    if (tex.x >= 0 && tex.x < texture->width && tex.y >= 0 && tex.y < texture->height)
    {
        // Calculate the pixel index in the texture's buffer
        pixelIndex = (tex.y * texture->width + tex.x) * (texture->bpp / 8);

        // Get the address of the pixel in the buffer
        pixelData = texture->buff + pixelIndex;

        // Read the color (assuming it's stored as a 32-bit integer, RGBA)
        if (texture->endian == 0)
        {
            // If the image is in big-endian format, read the color accordingly
            color = (pixelData[0] << 24) | (pixelData[1] << 16) | (pixelData[2] << 8) | pixelData[3];
        }
        else
        {
            // If the image is in little-endian format, read the color accordingly
            color = (pixelData[3] << 24) | (pixelData[2] << 16) | (pixelData[1] << 8) | pixelData[0];
        }

        // Place the pixel on the screen at the corresponding position
        // screenX and screenY are now integers
        game->screen_data[screenY * WIN_WIDTH + screenX] = color;
    }
}


void render_walls(t_game *game, t_ray *rays, t_player *player)
{
	int x, y;
	int lineHeight;
	int drawStart, drawEnd;
	t_image *texture; // The texture for the wall
	t_vector tex;	  // Coordinates for the texture
	(void)player;

	// Loop through all rays for each column
	for (x = 0; x < WIN_WIDTH; x++)
	{
		// Calculate the height of the wall line based on the ray distance
		lineHeight = (int)(WIN_HEIGHT / rays[x].dist);
		//printf("Ray %d distance: %f\n", x, rays[x].dist);  //
		// Calculate where to start and end drawing the wall
		drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;

		if (drawStart < 0)
			drawStart = 0;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		// Select the appropriate wall texture (you could choose based on side or other criteria)
		texture = game->textures->east;

		// Set the correct texture x-coordinate based on which side of the wall was hit
		tex.x = rays[x].tex_x;

		// Now loop through each pixel in the wall's height and draw the texture
		for (y = drawStart; y < drawEnd; y++)
		{
			// Calculate the texture y-coordinate based on the pixel's position
			tex.y = (y * texture->height) / lineHeight;

			// Now put the pixel from the texture onto the screen
			put_pixel_from_texture(game, texture, tex, (t_vector){x, y});
		}
	}
}

void put_pixel(t_game *game, int x, int y, int color)
{
    mlx_pixel_put(game->mlx, game->win, x, y, color);
}


void render_floor_and_ceiling(t_game *game, t_player *player)
{
	int x, y;
	int floor_color, ceiling_color;
	(void)player;

	// Dereference the color pointers to get the actual color values
	floor_color = *game->floor_color;
	ceiling_color = *game->ceiling_color;

	// Loop through the screen pixels
	for (x = 0; x < WIN_WIDTH; x++)
	{
		for (y = 0; y < WIN_HEIGHT; y++)
		{
			if (y < WIN_HEIGHT / 2) // If it's above the wall, render the ceiling
			{
				// Render the ceiling as a solid color
				put_pixel(game, x, y, ceiling_color); // put_pixel is a function to draw pixels
			}
			else // If it's below the wall, render the floor
			{
				// Render the floor as a solid color
				put_pixel(game, x, y, floor_color); // put_pixel is a function to draw pixels
			}
		}
	}
}

int render_scene(t_game *game, t_player *player)
{
	t_ray *rays;
	(void)player;
	// Cast rays
	rays = raycasting(game);
    mlx_clear_window(game->mlx, game->win);  // Clear the window

    // Now render the actual game scene
    render_walls(game, rays, player);
   	render_floor_and_ceiling(game, player);

	// Refresh the screen with new frame
	// Use the appropriate library or framework function to refresh the screen
	return 0;
}
