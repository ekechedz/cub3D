#include "../../include/cub3d.h"
#include <float.h>

// /* Each ray’s direction is determined using this formula:

// rayDirX = dirX + planeX × cameraX
// rayDirY = dirY + planeY × camera X

//   Where :

// 	dirX, dirY → Player’s view direction(where they’re looking).
// 	planeX, planeY → Camera plane(controls FOV).
// 	cameraX → Position of the column relative to the center of the screen.

// The cameraX value determines how far left or right a ray is cast.

// The center of the screen has cameraX = 0.
// The leftmost pixel has cameraX = -1.
// The rightmost pixel has cameraX = 1.
// The formula for cameraX is:

// cameraX = 2 × (column / screenWidth) - 1

// This ensures:

// cameraX = -1 at leftmost column.
// cameraX = 0 at center column.
// cameraX = 1 at rightmost column.

// */
// #include <float.h>
// #include <stdio.h>

// t_ray *raycasting(t_game *game)
// {
// 	int x;
// 	double cameraX, rayDirX, rayDirY;
// 	double deltaDistX, deltaDistY;
// 	double sideDistX, sideDistY;
// 	int mapX, mapY;
// 	int stepX, stepY;
// 	int hit, side;
// 	char **map = game->map->grid;
// 	t_ray *ray;
// 	// t_ray *rays = malloc(sizeof(t_ray) * WIN_WIDTH);
// 	// if (!rays)
// 	// {
// 	// 	fprintf(stderr, "Memory allocation failed for rays\n");
// 	// 	exit(EXIT_FAILURE);
// 	// }

// 	printf("Player starting position: (%f, %f)\n", game->player->pos->x, game->player->pos->y);

// 	for (x = 0; x < WIN_WIDTH; x++)
// 	{
// 		ray = init_ray();
// 		ray->hit = init_vector(0, 0);
// 		hit = 0;

// 		cameraX = 2 * (double)x / WIN_WIDTH - 1;
// 		rayDirX = game->player->dir->x + game->player->plane->x * cameraX;
// 		rayDirY = game->player->dir->y + game->player->plane->y * cameraX;

// 		//printf("\nColumn %d: cameraX = %f, rayDirX = %f, rayDirY = %f\n", x, cameraX, rayDirX, rayDirY);

// 		mapX = (int)game->player->pos->x;
// 		mapY = (int)game->player->pos->y;

// 		//printf("Starting grid cell: (%d, %d)\n", mapX, mapY);
// 	// Calculate delta distance (steps for each direction)
// 		deltaDistX = fabs(1 / rayDirX); // step size in the X direction
// 		deltaDistY = fabs(1 / rayDirY); // step size in the Y direction

// 	// Determine which direction we should step
// 		if (rayDirX < 0) {
// 			stepX = -1;
// 			sideDistX = (game->player->pos->x - mapX) * deltaDistX;
// 		} else {
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - game->player->pos->x) * deltaDistX;
// 		}

// 		if (rayDirY < 0) {
// 			stepY = -1;
// 			sideDistY = (game->player->pos->y - mapY) * deltaDistY;
// 		} else {
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - game->player->pos->y) * deltaDistY;
// 		}

// 		//printf("StepX: %d, StepY: %d, SideDistX: %f, SideDistY: %f\n", stepX, stepY, sideDistX, sideDistY);

// 		while (hit == 0)
// 		{
// 			if (sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}

// 			//printf("Stepping to: (%d, %d), side = %d\n", mapX, mapY, side);

// 			if (mapX < 0 || mapX >= game->map->width || mapY < 0 || mapY >= game->map->height)
// 			{
// 				hit = 1;
// 				printf("Ray out of bounds at: (%d, %d)\n", mapX, mapY);
// 				break;
// 			}

// 			if (map[mapX][mapY] == '1')
// 			{
// 				hit = 1;
// 				//printf("Wall hit at: (%d, %d)\n", mapX, mapY);
// 			}
// 		}

// 		double perpWallDist = (side == 0) ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY);
// 		// printf("Perpendicular Wall Distance: %f\n", perpWallDist);

// 		ray->dist = perpWallDist;
// 		ray->hit->x = mapX;
// 		ray->hit->y = mapY;
// 		ray->side = side;

// 		double wallX;
// 		if (side == 0)
// 			wallX = game->player->pos->y + perpWallDist * rayDirY;
// 		else
// 			wallX = game->player->pos->x + perpWallDist * rayDirX;

// 		wallX -= floor(wallX); // Get the fractional part of wall hit position

// 		int texWidth = 64;
// 		ray->tex_x = (int)(wallX * (double)texWidth);

// 		// Flip texture if necessary
// 		if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
// 			ray->tex_x = texWidth - ray->tex_x - 1;

// 		//printf("Texture X coordinate: %d\n", ray->tex_x);

// 		//printf("Perpendicular Wall Distance: %f\n", perpWallDist);
// 		ray->lineHeight = WIN_HEIGHT / perpWallDist;
// 		int drawStart = -ray->lineHeight / 2 + WIN_HEIGHT / 2;
// 		int drawEnd = ray->lineHeight / 2 + WIN_HEIGHT / 2;
// 		//printf("Perpendicular ray: %f\n", ray->lineHeight);
// 		if (drawStart < 0)
// 			drawStart = 0;
// 		if (drawEnd >= WIN_HEIGHT)
// 			drawEnd = WIN_HEIGHT - 1;

// 		printf("Draw Range: Start = %d, End = %d, Line Height = %f\n", drawStart, drawEnd, ray->lineHeight);
// 	}

// 	return ray;
// }

// 6. How to Proceed (Drawing the Line)

// To render the raycast results to the screen, you need to:

//     Use your graphics library (such as SDL, or whatever you're using) to draw the wall slice.
//     Loop through all the rays and draw them with the drawStart and drawEnd values.

// Here's a basic structure to draw the line in a graphics window:

// for (x = 0; x < WIN_WIDTH; x++) {
//     // 1. Camera transformation and ray direction calculation as before...

//     // 2. DDA loop to find where the ray hits a wall

//     // 3. Perpendicular distance and wall height calculation

//     // 4. Drawing the vertical line for the ray:
//     int color = getWallColor(side);  // You can color walls differently depending on side
//     for (int y = drawStart; y < drawEnd; y++) {
//         drawPixel(x, y, color);  // Draw pixel at (x, y) with the appropriate color
//     }
// }

//     getWallColor(side) can vary the color depending on which side (X or Y) the ray hits.
//     drawPixel(x, y, color) would be your graphics API function for drawing a pixel.

// Final Steps:

//     Integrate this rendering code into your game loop where you handle the screen buffer.
//     Test your raycasting with simple maps and ensure the walls are drawn correctly.
//     Adjust the FOV and other parameters to refine the visual effect.
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void put_pixel(t_game *game, int x, int y, int color);
int get_texture_color(t_image *texture, int x, int y);
void clear_screen(t_game *game);
void draw_floor_ceiling(t_game *game);
// Function to initialize a ray
void init_ray(t_game *game, t_ray *ray, double cameraX)
{
	ray->dist = 0;
	ray->hit = malloc(sizeof(t_vector));
	ray->side = -1;

	// Calculate the direction of the ray
	ray->hit->x = game->player->pos->x;
	ray->hit->y = game->player->pos->y;

	// Ray direction in X and Y based on the player's direction and the camera
	ray->dirX = game->player->dir->x + game->player->plane->x * cameraX;
	ray->dirY = game->player->dir->y + game->player->plane->y * cameraX;

	// Calculate the distance from the player to the wall in the X direction
	ray->deltaDistX = fabs(1.0 / ray->dirX);
	ray->deltaDistY = fabs(1.0 / ray->dirY);

	// Calculate step direction for X and Y
	if (ray->dirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->player->pos->x - (int)game->player->pos->x) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = ((int)game->player->pos->x + 1.0 - game->player->pos->x) * ray->deltaDistX;
	}

	if (ray->dirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->player->pos->y - (int)game->player->pos->y) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = ((int)game->player->pos->y + 1.0 - game->player->pos->y) * ray->deltaDistY;
	}
}

// Function to perform the DDA (Digital Differential Analyzer) algorithm
int dda_algorithm(t_game *game, t_ray *ray)
{
	// Initialize the distance to zero
	ray->dist = 0.0;

	while (1)
	{
		// Debugging prints to check distance and ray direction
		printf("Ray Position: (%f, %f), Ray Direction: (%f, %f), Distance: %f\n",
			   ray->hit->x, ray->hit->y, ray->dirX, ray->dirY, ray->dist);

		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->hit->x += ray->stepX;
			ray->side = 0; // Vertical hit
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->hit->y += ray->stepY;
			ray->side = 1; // Horizontal hit
		}

		// Increment the distance based on the step (moving along the ray direction)
		if (ray->side == 0)
			ray->dist += ray->deltaDistX; // Increase distance when moving in X direction
		else
			ray->dist += ray->deltaDistY; // Increase distance when moving in Y direction

		// If we hit a wall, break out
		if (game->map->grid[(int)ray->hit->y][(int)ray->hit->x] == '1')
			break;
	}

	// Debugging print after DDA loop ends
	printf("Final Hit Position: (%f, %f), Distance: %f\n", ray->hit->x, ray->hit->y, ray->dist);

	return 0;
}

// Function to calculate the height of the line to draw on the screen
void calculate_line_height(t_ray *ray, t_game *game, int x)
{
	(void)game;
	(void)x;
	ray->lineHeight = (int)(WIN_HEIGHT / ray->dist);

	// Calculate the start and end points of the vertical line
	ray->drawStart = -ray->lineHeight / 2 + WIN_HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + WIN_HEIGHT / 2;
	if (ray->drawEnd >= WIN_HEIGHT)
		ray->drawEnd = WIN_HEIGHT - 1;

	printf("line height: %f\n", ray->lineHeight);
	printf("drawStart: %i\n", ray->drawStart);
	printf("drawEnd: %i\n", ray->drawEnd);
}

// Function to get the X coordinate of the texture to draw
int get_tex_x(t_ray *ray, t_game *game)
{
	double wall_x;
	if (ray->side == 0)
	{
		// If we hit a vertical wall, calculate based on the Y-coordinate
		wall_x = game->player->pos->y + ray->dist * ray->dirY;
	}
	else
	{
		// If we hit a horizontal wall, calculate based on the X-coordinate
		wall_x = game->player->pos->x + ray->dist * ray->dirX;
	}

	// Calculate the fractional part of wall_x to determine the texture coordinate (TexX)
	wall_x -= floor(wall_x);						  // Fractional part of the wall_x
	int texX = (int)(wall_x * (double)TEXTURE_WIDTH); // Map it to the texture width

	// Print debugging info for texture coordinate calculation
	printf("Wall X (horizontal hit): %f\n", wall_x);
	printf("Wall X Fractional: %f\n", wall_x - floor(wall_x));
	printf("Computed TexX: %d\n", texX);

	return texX;
}

void	set_pixel(t_game *data, int c[3], int x, int y)
{
	int		color;
	char	*pixel;

	color = (c[0] * 256 * 256 + c[1] * 256 + c[2]);
	color = mlx_get_color_value(data->mlx, color);
	pixel = (char *)data->screen_data + y * WIN_WIDTH  * 4 + x * data->bpp / 8;
	ft_memcpy(pixel, &color, 4);
}

// Function to draw the ray on the screen
void draw_ray(t_game *game, t_ray *ray, int x)
{
	int texX = get_tex_x(ray, game);
	int texY;
	//int c[3] = {255, 0, 0};
	int color;

	// Loop through every pixel in the line
	for (int y = ray->drawStart; y < ray->drawEnd; y++)
	{
		// Get the y coordinate for the texture
		texY = (int)(y * 256 - WIN_HEIGHT * 128 + ray->lineHeight * 128) / ray->lineHeight / 256;

		// Draw the texture
		color = get_texture_color(game->textures->north, texX, texY); // Function to get pixel color from texture
		//color = (c[0] * 256 * 256 + c[1] * 256 + c[2]);
		put_pixel(game, x, y, color);
		printf("set pixel %d,%d\n", x, y);
		//set_pixel(game, (int[3]){255, 0, 0}, x, y);
	}
}
int get_texture_pixel(t_image *texture, int tex_x, int tex_y)
{
    // The formula converts tex_x and tex_y into an address in the texture's buffer.
    int *color = (int *)(texture->buff + (tex_y * texture->lstsize + tex_x * (texture->bpp / 8)));
    return *color;
}
void draw_wall_texture(t_game *game, int x, int wall_height, int tex_x, t_image *texture)
{
    int tex_y;
    int color;
    int wall_top = (WIN_HEIGHT / 2) - (wall_height / 2);
    int wall_bottom = (WIN_HEIGHT / 2) + (wall_height / 2);

    // Loop over the vertical wall slice
    for (int y = wall_top; y < wall_bottom; y++) {
        // Calculate the corresponding y position in the texture (based on ray distance)
        tex_y = (y - wall_top) * texture->height / wall_height;

        // Get the pixel color from the texture at TexX and TexY
        color = get_texture_pixel(texture, tex_x, tex_y);

        // Draw the pixel to the screen
        mlx_pixel_put(game->mlx, game->win, x, y, color);
    }
}


// Main raycasting function
void raycast(t_game *game)
{
	t_ray ray;
	double cameraX;
	for (int x = 0; x < WIN_HEIGHT; x++)
	{
		cameraX = 2 * x / (double)WIN_HEIGHT - 1; // X-coordinate in camera space
		init_ray(game, &ray, cameraX);
		dda_algorithm(game, &ray);
		calculate_line_height(&ray, game, x);
		draw_ray(game, &ray, x);
	}
}

// Function to draw a pixel on the screen
void put_pixel(t_game *game, int x, int y, int color)
{
	int *pixel = game->screen_data + y * WIN_WIDTH + x;
	*pixel = color;
}

// Function to get the color of a pixel from the texture
int get_texture_color(t_image *texture, int x, int y)
{
	int color;
	int i = (y * texture->lstsize) + x * (texture->bpp / 8);
	color = *(int *)(texture->buff + i);
	return color;
}

void render(t_game *game)
{
	// Clear the screen (you can fill the screen with a color like the sky color or black)
	clear_screen(game);

	// Draw floor and ceiling (optional but necessary for full rendering)
	draw_floor_ceiling(game);

	// Raycasting to calculate and draw the walls
	raycast(game);

	// Update the display
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

// Function to clear the screen
void clear_screen(t_game *game)
{
	// Loop through all pixels and set them to the background color (e.g., black or sky color)
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			put_pixel(game, x, y, 0x000080); // Set background color to black
		}
	}
}

// Function to draw the floor and ceiling
void draw_floor_ceiling(t_game *game)
{
	int color;

	// Draw the ceiling (assuming ceiling_color is assigned)
	color = *game->ceiling_color;
	for (int y = 0; y < WIN_HEIGHT / 2; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			put_pixel(game, x, y, color); // Draw the ceiling (top half)
		}
	}

	// Draw the floor (assuming floor_color is assigned)
	color = *game->floor_color;
	for (int y = WIN_HEIGHT / 2; y < WIN_HEIGHT; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			put_pixel(game, x, y, color); // Draw the floor (bottom half)
		}
	}
}

// Main function to run the game loop and handle events
int main_loop(t_game *game)
{
	// In the game loop, render the frame
	render(game);
	render_minimap(game->mlx, game->win, game->config);
	// Optionally, you can add code to handle player movement, camera rotation, and game logic here
	return 0;
}
