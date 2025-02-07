// #include "../../include/cub3d.h"

// int get_tex_color(t_image *texture, int x, int y);
// int render_frame(t_game *game);
// t_image *select_texture(t_game *game, t_ray *ray);
// void draw_floors(t_game *g);

// void my_mlx_pixel_put(t_game *game, int x, int y, int color)
// {
// 	int offset;
// 	if (!game->addr)
// 	{
// 		fprintf(stderr, "Error: Trying to write to an invalid image buffer\n");
// 		return;
// 	}

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
// 		tex_y = (int)tex_pos & (texture->height - 1); // ensures that tex_y is within texture bounds
// 		color = get_tex_color(texture, tex_x, tex_y);
// 		my_mlx_pixel_put(game, x, y, color);
// 		tex_pos += step;
// 			//printf("Raycasting column %d: tex_x = %d, tex_y = %d, draw_start = %d, draw_end = %d\n",
//       	// x, tex_x, tex_y, ray->drawStart, ray->drawEnd);
// 		y++;
// 	}
// }

// int render_frame(t_game *game)
// {
// 	int x;
// 	t_ray ray;
// 	t_image *texture;

// 	printf("Debug: Rendering new frame...\n"); // Check if render_frame is being called
// 	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
// 	if (!game->img)
// 	{
// 		fprintf(stderr, "Error: mlx_new_image() failed\n");
// 		return (1);
// 	}

// 	//printf("Debug: Image created at address = %p\n", game->img);

// 	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->line_length, &game->endian);
// 	if (!game->addr)
// 	{
// 		fprintf(stderr, "Error: mlx_get_data_addr() failed\n");
// 		return (1);
// 	}

// 	//printf("Debug: Image Addr = %p, bpp = %d, line_length = %d, endian = %d\n",
// 		 //  game->addr, game->bpp, game->line_length, game->endian);

// 	draw_floors(game);

// 	x = 0;
// 	while (x < WIN_WIDTH)
// 	{
// 		//printf("Debug: Processing column %d...\n", x); // Track x position
// 		ray = raycasting(game, x);


// 		texture = select_texture(game, &ray);
// 		if (!texture)
// 		{
// 			printf("Debug: Texture selection failed for ray at column %d\n", x);
// 		}

// 		draw_textured_wall(game, x, &ray, texture);
// 		x++;
// 	}

// 	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
// 	//printf("Debug: Frame rendered and image put to window.\n");
// 	//usleep(10000);
// 	return (0);
// }

// int get_tex_color(t_image *texture, int x, int y)
// {
// 	x = x % texture->width; // Wrap tex_x around the texture width if it's out of bounds
//     int offset = (y * texture->width) + (x * (texture->bpp / 8)); // Use texture->width here, not lstsize
//     return *(unsigned int *)(texture->buff + offset);
// }

// t_image *select_texture(t_game *game, t_ray *ray)
// {
// 	if (ray->side == 0) // Check if the wall hit was horizontal or vertical
// 		return (game->player->dir->x > 0) ? game->textures->east : game->textures->west;
// 	else
// 		return (game->player->dir->y > 0) ? game->textures->south : game->textures->north;
// }

// void draw_floors(t_game *g)
// {
// 	int x;
// 	int y;

// 	y = -1;
// 	while (y++ < WIN_HEIGHT / 2)
// 	{
// 		x = -1;
// 		while (++x < WIN_WIDTH)
// 			my_mlx_pixel_put(g, x, y, *g->ceiling_color);
// 	}
// 	while (y++ < WIN_HEIGHT)
// 	{
// 		x = -1;
// 		while (++x < WIN_WIDTH)
// 			my_mlx_pixel_put(g, x, y, *g->floor_color);
// 	}
// }
