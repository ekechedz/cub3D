#include "../include/cub3d.h"

int	get_txt_color(t_image *txt, int x, int y)
{
	int	color;
	int	i;
	
	color = 0;
	if (!txt || x < 0 || y < 0 || x >= txt->width || y >= txt->height)
		return (0);
	i = (y * txt->width + x) * (txt->bpp / 8);
	if (i + (txt->bpp / 8) > txt->width * txt->height * (txt->bpp / 8))
		return (0);
	color = *(int *)(txt->buff + i);
	return (color);
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