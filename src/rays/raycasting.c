#include "../../include/cub3d.h"

void draw_floor_ceiling(t_game *game);
// Function to draw a pixel on the screen
void put_pixel(t_game *game, int x, int y, int color)
{
	int *pixel = game->screen_data + y * WIN_WIDTH + x;
	*pixel = color;
}

// Function to get the color of a pixel from the texture
int get_texture_color(t_image *texture, int x, int y)
{
	int color = 0;

	// Ensure x and y are within bounds
	if (!texture || x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return 0; // Return a default color (black) or handle the error

	// Calculate the byte offset based on the texture's line size (lstsize)
int i = (y * texture->width + x) * (texture->bpp / 8);

	// Ensure we are not reading out of bounds
	if (i + (texture->bpp / 8) > texture->width * texture->height * (texture->bpp / 8))
		return 0;

	// Directly read the color value at the pixel (x, y) from the buffer
	color = *(int *)(texture->buff + i); // Assuming the texture buffer is in 32-bit color format (RGBA or RGB)

	return color;
}

void initialize_ray(t_game *game, t_ray *ray, int x)
{
	double cameraX = 2 * x / (double)WIN_WIDTH - 1; // Range [-1, 1]

	// Initialize the ray properties
	ray->posX = game->player->pos->x;
	ray->posY = game->player->pos->y;
	ray->dirX = game->player->dir->x + game->player->plane->x * cameraX;
	ray->dirY = game->player->dir->y + game->player->plane->y * cameraX;

	ray->deltaDistX = fabs(1 / ray->dirX);
	ray->deltaDistY = fabs(1 / ray->dirY);

	ray->hit = (t_vector *)malloc(sizeof(t_vector));
	ray->hit->x = ray->posX;
	ray->hit->y = ray->posY;

	// Set up DDA step and side distance
	if (ray->dirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (ray->posX - (int)ray->posX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = ((int)ray->posX + 1.0 - ray->posX) * ray->deltaDistX;
	}

	if (ray->dirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (ray->posY - (int)ray->posY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = ((int)ray->posY + 1.0 - ray->posY) * ray->deltaDistY;
	}
}

int perform_dda(t_game *game, t_ray *ray)
{
	int hit = 0;

	while (hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->hit->x += ray->stepX;
			ray->side = 0; // Vertical wall hit
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->hit->y += ray->stepY;
			ray->side = 1; // Horizontal wall hit
		}

		if (game->map->grid[(int)ray->hit->y][(int)ray->hit->x] == WALL)
		{
			hit = 1;
		}
	}

	return hit;
}

void render_texture(t_game *game, t_ray *ray, int x)
{
	double	wallX;
	int		texX;

	if (ray->side == 0)
		ray->perpWallDist = (ray->hit->x - ray->posX + (1 - ray->stepX) / 2) / ray->dirX;
	else
		ray->perpWallDist = (ray->hit->y - ray->posY + (1 - ray->stepY) / 2) / ray->dirY;

	ray->lineHeight = (int)(WIN_HEIGHT / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + WIN_HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + WIN_HEIGHT / 2;
	if (ray->drawEnd >= WIN_HEIGHT)
		ray->drawEnd = WIN_HEIGHT - 1;
	if (ray->side == 0)
		wallX = ray->posY + ray->perpWallDist * ray->dirY;
	else
		wallX = ray->posX + ray->perpWallDist * ray->dirX;
	wallX -= floor(wallX);
	texX = (int)(wallX * (double)TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->dirX > 0) || (ray->side == 1 && ray->dirY < 0))
		texX = TEXTURE_WIDTH - texX - 1;
	render_slice(ray, texX, x, game);
}

int	render_slice(t_ray *ray, int texX, int x, t_game *game)
{
	int		y;
	int		texY;
	int		color;
	t_image	*texture;

	y = ray->drawStart;
	texture = choose_texture(ray, game);
	while (y < ray->drawEnd)
	{
		texY = (((y - WIN_HEIGHT / 2 + ray->lineHeight / 2) * TEXTURE_HEIGHT) / ray->lineHeight);
		if (texY < 0)
			texY = 0;
		if (texY >= TEXTURE_HEIGHT)
			texY = TEXTURE_HEIGHT - 1;
		color = get_texture_color(texture, texX, texY);
		game->screen_data[y * WIN_WIDTH + x] = color;
		y ++;
	}
	return (0);
}

t_image	*choose_texture(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
	{
		if (ray->dirX > 0)
			return (game->textures->east);
		else
			return (game->textures->west);
	}
	else
	{
		if (ray->dirY > 0)
			return (game->textures->south);
		else
			return (game->textures->north);
	}
}

void cast_rays(t_game *game)
{
	int x;
	t_ray ray;

	for (x = 0; x < WIN_WIDTH; x++)
	{
		initialize_ray(game, &ray, x);
		if (perform_dda(game, &ray))
			render_texture(game, &ray, x);
	}
}

void render(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_floor_ceiling(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

// Function to clear the screen
// void clear_screen(t_game *game)
// {
// 	// Loop through all pixels and set them to the background color (e.g., black or sky color)
// 	for (int y = 0; y < WIN_HEIGHT; y++)
// 	{
// 		for (int x = 0; x < WIN_WIDTH; x++)
// 		{
// 			put_pixel(game, x, y, 0x002000); // Set background color to black
// 		}
// 	}
// }

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
#include <sys/time.h>
// Main function to run the game loop and handle events
int main_loop(t_game *game)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL); // Get the current time

	// Calculate delta_time in seconds
	double delta_time = (current_time.tv_sec - game->last_time.tv_sec) +
						(current_time.tv_usec - game->last_time.tv_usec) / 1000000.0;

	// Update last_time for the next frame
	game->last_time = current_time;

	// Handle continuous movement based on key state
	if (game->key_state[119])
	{									  // W key (move forward)
		move_player(game, 1, delta_time); // Move forward
	}
	if (game->key_state[115])
	{									   // S key (move backward)
		move_player(game, -1, delta_time); // Move backward
	}
	if (game->key_state[97])
	{										 // A key (strafe left)
		strafe_player(game, -1, delta_time); // Strafe left
	}
	if (game->key_state[100])
	{										// D key (strafe right)
		strafe_player(game, 1, delta_time); // Strafe right
	}
	if (game->key_state[65361])
	{										 // Left arrow key (rotate left)
		rotate_player(game, -1, delta_time); // Rotate left
	}
	if (game->key_state[65363])
	{										// Right arrow key (rotate right)
		rotate_player(game, 1, delta_time); // Rotate right
	}
	// In the game loop, render the frame
	render(game);
	// render_minimap(game->mlx, game->win, game->config);
	//   Optionally, you can add code to handle player movement, camera rotation, and game logic here
	return 0;
}
