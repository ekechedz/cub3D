#include "../../include/cub3d.h"

static void put_pixel(t_game *game, int x, int y, int color);

void	render(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	memset(game->screen_data, 0, WIN_WIDTH * WIN_HEIGHT * sizeof(int));
	draw_floor_ceiling(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void render_texture(t_game *game, t_ray *ray, int x)
{
	double	wallX;
	int		texX;

	if (ray->side == 0)
		ray->perpWallDist = (ray->hit->x - ray->posX + (1 - ray->stepX) / 2) / ray->dirX;
	else
		ray->perpWallDist = (ray->hit->y - ray->posY + (1 - ray->stepY) / 2) / ray->dirY;
	
	if (ray->perpWallDist <= 0) 
    	ray->perpWallDist = 0.01; // Avoid division by zero
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
		color = get_txt_color(texture, texX, texY);
		game->screen_data[y * WIN_WIDTH + x] = color;
		y ++;
	}
	return (0);
}

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

static void put_pixel(t_game *game, int x, int y, int color)
{
	int	*pixel;
	
	pixel = game->screen_data + y * WIN_WIDTH + x;
	*pixel = color;
}