#include "../../include/cub3d.h"
#include <ctype.h>

void trim_whitespace(char *str)
{
	if (str == NULL)
    {
        return; // Handle NULL input gracefully.
    }
	int start = 0;
	int end = ft_strlen(str) - 1;

	// Trim leading spaces
	while (isspace((unsigned char)str[start]))
		start++;

	// Trim trailing spaces
	while (end > start && isspace((unsigned char)str[end]))
		end--;

	// Shift characters forward and null-terminate
	int i;
	for (i = 0; start <= end; start++, i++)
		str[i] = str[start];
	str[i] = '\0';
}

int load_image(void *mlx_ptr, t_image *img, char *fname)
{
	trim_whitespace(fname);
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, fname, &img->width,
										 &img->height);
	if (img->img_ptr == NULL)
		return (-1);
	img->buff = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->lstsize,
								  &img->endian);
	return (0);
}

int load_textures(t_game *game, t_config *config)
{

	trim_whitespace(config->textures->north->img_ptr);
	trim_whitespace(config->textures->south->img_ptr);
	trim_whitespace(config->textures->east->img_ptr);
	trim_whitespace(config->textures->west->img_ptr);


	if (load_image(game->mlx, game->textures->north, config->textures->north->img_ptr) == -1 ||
			 load_image(game->mlx, game->textures->east, config->textures->east->img_ptr) == -1 ||
			 load_image(game->mlx, game->textures->west, config->textures->west->img_ptr) == -1 ||
			 load_image(game->mlx, game->textures->south, config->textures->south->img_ptr) == -1)
		exit_with_error("Failed to load wall textures\n", 1);

	game->floor_color = config->floor_color; // Assign RGB floor color
	game->ceiling_color = config->ceiling_color;

	return (0);
}
