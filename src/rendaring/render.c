// #include "../../include/cub3d.h"

// // void put_pixel_from_texture(t_game *game, t_image *texture, t_vector tex, t_vector screen)
// // {
// // 	int color;
// // 	int pixelIndex;
// // 	char *pixelData;

// // 	// Convert screen.x and screen.y to integers
// // 	int screenX = (int)screen.x;
// // 	int screenY = (int)screen.y;

// // 	// Make sure the texture coordinates are within bounds
// // 	if (tex.x >= 0 && tex.x < texture->width && tex.y >= 0 && tex.y < texture->height)
// // 	{
// // 		// Calculate the pixel index in the texture's buffer
// // 		pixelIndex = (tex.y * texture->width + tex.x) * (texture->bpp / 8);

// // 		// Get the address of the pixel in the buffer
// // 		pixelData = texture->buff + pixelIndex;

// // 		// Read the color (assuming it's stored as a 32-bit integer, RGBA)
// // 		if (texture->endian == 0)
// // 		{
// // 			// If the image is in big-endian format, read the color accordingly
// // 			color = (pixelData[0] << 24) | (pixelData[1] << 16) | (pixelData[2] << 8) | pixelData[3];
// // 		}
// // 		else
// // 		{
// // 			// If the image is in little-endian format, read the color accordingly
// // 			color = (pixelData[3] << 24) | (pixelData[2] << 16) | (pixelData[1] << 8) | pixelData[0];
// // 		}

// // 		// Place the pixel on the screen at the corresponding position
// // 		// screenX and screenY are now integers
// // 		game->screen_data[screenY * WIN_WIDTH + screenX] = color;
// // 	}
// // }

// // void put_pixel(t_game *game, int x, int y, int color)
// // {
// // 	mlx_pixel_put(game->mlx, game->win, x, y, color);
// // }
// int get_tex_color(t_image *texture, int x, int y);
// void my_mlx_pixel_put(t_game *game, int x, int y, int color)
// {
// 	int offset;

// 	if (x >= 0 && x < 800 && y >= 0 && y < 600)
// 	{
// 		offset = (y * game->line_length) + (x * (game->bpp / 8));
// 		*(unsigned int *)(game->addr + offset) = color;
// 	}
// }


// void draw_textured_wall(t_game *game, int x, t_ray *ray, t_image *texture)
// {
// 	int y = ray->drawStart;
// 	double step = (double)texture->height / ray->lineHeight;
// 	double tex_pos = 0.0;
// 	int tex_x = ray->tex_x;
// 	int tex_y;
// 	int color;

// 	while (y < ray->drawEnd)
// 	{
// 		tex_y = (int)tex_pos & (texture->height - 1);  // ensures that tex_y is within texture bounds
// 		color = get_tex_color(texture, tex_x, tex_y);
// 		my_mlx_pixel_put(game, x, y, color);
// 		tex_pos += step;
// 		y++;
// 	}
// }
// int get_tex_color(t_image *texture, int x, int y)
// {
// 	int offset = (y * texture->lstsize) + (x * (texture->bpp / 8));
// 	return *(unsigned int *)(texture->buff + offset);
// }


// void render_floor_and_ceiling(t_ray *ray, t_game *game, t_player *player)
// {
// 	int x, y;
// 	int floor_color, ceiling_color;
// 	float	wall_height;
// 	(void)player;


// 	floor_color = *game->floor_color;
// 	ceiling_color = *game->ceiling_color;

// 	t_vector tex;
// 	t_vector screen;


// 	// Loop through the screen pixels

// 	wall_height = ray->lineHeight;
// 	printf("wall121321 height %f\n", wall_height);
// 	for (x = 0; x < WIN_WIDTH; x++)
// 	{
// 		for (y = 0; y < WIN_HEIGHT; y++)
// 		{
// 			if (y < (WIN_HEIGHT - wall_height) / 2) // If it's above the wall, render the ceiling
// 			{
// 				// Render the ceiling as a solid color
// 				put_pixel(game, x, y, ceiling_color); // put_pixel is a function to draw pixels
// 			}
// 			else if (y < (WIN_HEIGHT - wall_height) / 2 + wall_height)
// 			{
// 				screen.x = x;
// 				screen.y = y;

// 				tex.x = (int)(x % game->textures->east->width);
// 				tex.y = (int)((y % game->textures->east->height) * (game->textures->east->height / wall_height));

// 				put_pixel_from_texture(game, game->textures->east, tex, screen);
// 			}

// 			else // If it's below the wall, render the floor
// 			{
// 				// Render the floor as a solid color
// 				put_pixel(game, x, y, floor_color); // put_pixel is a function to draw pixels
// 			}
// 		}
// 	}
// }

// int render_scene(t_game *game, t_player *player)
// {
// 	t_ray ray;
// 	(void)player;
// 	int x;
// 	// Cast rays
// 	x = 0;
// 	while(x < WIN_WIDTH)
// 	{
// 		ray = raycasting(game, x);
// 		render_floor_and_ceiling(&ray, game, player);
// 		x++;
// 	}

// 	//mlx_clear_window(game->mlx, game->win); // Clear the window

// 	// Now render the actual game scene
// 	//render_walls(game, rays);


// 	// Refresh the screen with new frame
// 	// Use the appropriate library or framework function to refresh the screen
// 	return 0;
// }
