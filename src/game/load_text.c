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
	if (!mlx_ptr || !img || !fname)
        return (-1); // Avoid null pointer crashes
    img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, fname, &img->width, \
		&img->height);
	if (img->img_ptr == NULL)
		return (-1);
	img->buff = mlx_get_data_addr(img->img_ptr, &img->bpp, \
		&img->lstsize, &img->endian);
	return (0);
}

int load_textures(t_game *game, t_config *config)
{
    if (!game || !config || !config->textures)
        return (-1); // Prevent null pointer crashes

    // Trim and validate texture file paths before loading
    if (config->textures->north && config->textures->north->file_path)
        trim_whitespace(config->textures->north->file_path);
    if (config->textures->south && config->textures->south->file_path)
        trim_whitespace(config->textures->south->file_path);
    if (config->textures->east && config->textures->east->file_path)
        trim_whitespace(config->textures->east->file_path);
    if (config->textures->west && config->textures->west->file_path)
        trim_whitespace(config->textures->west->file_path);

    // Load images while checking for errors
    if (load_image(game->mlx, game->textures->north, config->textures->north->file_path) == -1 ||
        load_image(game->mlx, game->textures->east, config->textures->east->file_path) == -1 ||
        load_image(game->mlx, game->textures->west, config->textures->west->file_path) == -1 ||
        load_image(game->mlx, game->textures->south, config->textures->south->file_path) == -1)
        return (-1);
    game->floor_color = config->floor_color;
    game->ceiling_color = config->ceiling_color;

    return (0);
}
