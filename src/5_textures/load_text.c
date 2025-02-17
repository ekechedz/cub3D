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

int	load_img(void *mlx_ptr, t_image *img, char *fname)
{
	if (!mlx_ptr || !img || !fname)
		return (-1);
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, fname, &img->width, \
		&img->height);
	if (img->img_ptr == NULL)
		return (-1);
	img->buff = mlx_get_data_addr(img->img_ptr, &img->bpp, \
		&img->lstsize, &img->endian);
	return (0);
}

int	load_textures(t_game *g, t_config *config)
{
	if (!g || !config || !config->textures)
		return (-1);
	if (config->textures->north && config->textures->north->fp)
		trim_whitespace(config->textures->north->fp);
	if (config->textures->south && config->textures->south->fp)
		trim_whitespace(config->textures->south->fp);
	if (config->textures->east && config->textures->east->fp)
		trim_whitespace(config->textures->east->fp);
	if (config->textures->west && config->textures->west->fp)
		trim_whitespace(config->textures->west->fp);
	if (load_img(g->mlx, g->textures->north, config->textures->north->fp) == -1 \
	|| load_img(g->mlx, g->textures->east, config->textures->east->fp) == -1 \
	|| load_img(g->mlx, g->textures->west, config->textures->west->fp) == -1 \
	|| load_img(g->mlx, g->textures->south, config->textures->south->fp) == -1)
		return (-1);
	g->floor_color = config->floor_color;
	g->ceiling_color = config->ceiling_color;
	return (0);
}
