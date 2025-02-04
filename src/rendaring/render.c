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

void render_walls(t_game *game, t_ray *rays)
{
	int x, y;
	int lineHeight;
	int drawStart, drawEnd;
	t_image *texture;
	t_vector hit;	 // To store the exact hit position on the wall
	//t_vector rayDir; // Ray direction

	for (x = 0; x < WIN_WIDTH; x++)
	{
		// 1. Calculate the distance of the ray
		lineHeight = (int)(WIN_HEIGHT / rays[x].dist);

		// Debugging: Output the ray distance and line height
		printf("Ray %d - dist: %.2f, lineHeight: %d\n", x, rays[x].dist, lineHeight);

		// 2. Calculate the start and end points for the wall slice
		drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		// Debugging: Output the draw start and end points
		printf("Ray %d - drawStart: %d, drawEnd: %d\n", x, drawStart, drawEnd);

		// 3. Select the correct texture for the wall depending on the side of the hit
		if (rays[x].side == 0)
		{
			texture = game->textures->north; // Assume north texture for vertical hits
		}
		else
		{
			texture = game->textures->east; // Assume east texture for horizontal hits
		}

		// Debugging: Output which texture we're using
		printf("Ray %d - Texture: %s\n", x, (rays[x].side == 0) ? "North" : "East");

		// 4. Calculate texture coordinates (tex.x, tex.y)
		hit = *rays[x].hit;							   // Get the exact hit position on the wall (as a vector)
		rays[x].tex_x = (int)(hit.x * texture->width); // Wall hit X position mapped to texture width
		if (rays[x].side == 0 && rays[x].hit->x > 0)
		{
			rays[x].tex_x = texture->width - rays[x].tex_x - 1;
		}
		if (rays[x].side == 1 && rays[x].hit->y < 0)
		{
			rays[x].tex_x = texture->width - rays[x].tex_x - 1;
		}

		// Debugging: Output texture coordinates
		printf("Ray %d - tex_x: %d, tex_y: %d\n", x, rays[x].tex_x, (int)(hit.y * texture->height));

		// 5. Texture vertical position (tex.y)
		int tex_y = (int)(hit.y * texture->height) % texture->height;

		// Debugging: Output the texture Y position
		printf("Ray %d - tex_y: %d\n", x, tex_y);

		// 6. Draw the wall slice (vertical line)
		for (y = drawStart; y < drawEnd; y++)
		{
			int color = texture->buff[tex_y * texture->width + rays[x].tex_x]; // Get pixel from texture buffer
			//game->screen_data[y * WIN_WIDTH + x] = color;					   // Set the color on the screen buffer

			// Debugging: Show the color being drawn (in hex)
			printf("Ray %d - Drawing pixel at (%d, %d) with color: %#010x\n", x, x, y, color);
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
	float	wall_height;
	(void)player;

	// Dereference the color pointers to get the actual color values
	floor_color = *game->floor_color;
	ceiling_color = *game->ceiling_color;

	t_vector tex;
	t_vector screen;


	// Loop through the screen pixels
	wall_height = 200;
	for (x = 0; x < WIN_WIDTH; x++)
	{
		for (y = 0; y < WIN_HEIGHT; y++)
		{
			if (y < (WIN_HEIGHT - wall_height) / 2) // If it's above the wall, render the ceiling
			{
				// Render the ceiling as a solid color
				put_pixel(game, x, y, ceiling_color); // put_pixel is a function to draw pixels
			}
			else if (y < (WIN_HEIGHT - wall_height) / 2 + wall_height)
				put_pixel_from_texture(game, game->textures->east, tex, screen);
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
	//mlx_clear_window(game->mlx, game->win); // Clear the window

	(void)rays;
	// Now render the actual game scene
	//render_walls(game, rays);
	render_floor_and_ceiling(game, player);

	// Refresh the screen with new frame
	// Use the appropriate library or framework function to refresh the screen
	return 0;
}
