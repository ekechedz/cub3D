/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:39:06 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/14 16:37:38 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/cub3d.h"
#include <ctype.h>

int	load_image(void *mlx_ptr, t_image *img, char *fname)
{
	trim_whitespace(fname);
	if (img->img_ptr)
	{
		free(img->img_ptr);
		img->img_ptr = NULL;
	}
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, fname, &img->width, \
		&img->height);
	if (img->img_ptr == NULL)
		return (-1);
	img->buff = mlx_get_data_addr(img->img_ptr, &img->bpp, \
		&img->lstsize, &img->endian);
	return (0);
}

int	load_textures(t_game *game, t_config *config)
{
	trim_whitespace(config->textures->north->img_ptr);
	trim_whitespace(config->textures->south->img_ptr);
	trim_whitespace(config->textures->east->img_ptr);
	trim_whitespace(config->textures->west->img_ptr);
	if (load_image(game->mlx, game->textures->north, \
		config->textures->north->img_ptr) == -1 || load_image(game->mlx, \
			game->textures->east, config->textures->east->img_ptr) == -1 \
			|| load_image(game->mlx, game->textures->west, \
				config->textures->west->img_ptr) == -1 || \
				load_image(game->mlx, game->textures->south, \
					config->textures->south->img_ptr) == -1)
		return -1;
	game->floor_color = config->floor_color;
	game->ceiling_color = config->ceiling_color;
	return (0);
}
