#include "../../include/cub3d.h"

int load_textures(t_game *game, t_config *config)
{
	printf("Trying to load texture from: %s\n", game->config->textures->north->buff);
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("Current working directory: %s\n", cwd);
	}
	else
	{
		perror("getcwd error");
	}

	char abs_path[1024];
	realpath(game->config->textures->north->buff, abs_path);
	printf("Absolute path to texture: %s\n", abs_path);
	void *img = mlx_xpm_file_to_image(game->mlx, game->config->textures->north->buff, &game->textures->north->width, &game->textures->north->height);
	if (img == NULL)
	{
    	perror("mlx_xpm_file_to_image failed");
		printf("Check if the file exists: %s\n", game->config->textures->north->buff);
    	exit_with_error("Failed to load north texture\n", 1);
	}
	

	if (access(game->config->textures->north->buff, F_OK) != 0) {
		perror("Error checking texture file");
		exit_with_error("Texture file does not exist\n", 1);
	}

	//Load wall textures (north, south, east, west)
	if ((game->textures->north->img_ptr = mlx_xpm_file_to_image(game->mlx, game->config->textures->north->buff,
															  &game->textures->north->width, &game->textures->north->height)) == NULL ||
		(game->textures->south->img_ptr = mlx_xpm_file_to_image(game->mlx, game->config->textures->south->buff,
															  &game->textures->south->width, &game->textures->south->height)) == NULL ||
		(game->textures->east->img_ptr = mlx_xpm_file_to_image(game->mlx, game->config->textures->east->buff,
															 &game->textures->east->width, &game->textures->east->height)) == NULL ||
		(game->textures->west->img_ptr = mlx_xpm_file_to_image(game->mlx, game->config->textures->west->buff,
															 &game->textures->west->width, &game->textures->west->height)) == NULL)
		exit_with_error("Failed to load wall textures\n", 1);
	// config->textures->north->buff = "/home/ekechedz/cub3D/textures/wall.xpm";
	// config->textures->south->buff = "/home/ekechedz/cub3D/textures/wall.xpm";
	// config->textures->east->buff = "/home/ekechedz/cub3D/textures/wall.xpm";
	// config->textures->west->buff = "/home/ekechedz/cub3D/textures/wall.xpm";
	//printf("Trying to load texture from: %s\n", config->textures->north->buff);
	// if ((game->textures->north->img_ptr = mlx_xpm_file_to_image(game->mlx, config->textures->north->buff,
	// 														  &game->textures->north->width, &game->textures->north->height)) == NULL)
	// {
	// 	printf("Failed to load north texture: %s\n", config->textures->north->buff);
	// 	exit_with_error("Failed to load north texture\n", 1);
	// }

	// if ((game->textures->south->img_ptr = mlx_xpm_file_to_image(game->mlx, config->textures->south->buff,
	// 															&game->textures->south->width, &game->textures->south->height)) == NULL)
	// {
	// 	printf("Failed to load south texture: %s\n", config->textures->south->buff);
	// 	exit_with_error("Failed to load south texture\n", 1);
	// }

	// if ((game->textures->east->img_ptr = mlx_xpm_file_to_image(game->mlx, config->textures->east->buff,
	// 															&game->textures->east->width, &game->textures->east->height)) == NULL)
	// {
	// 	printf("Failed to load east texture: %s\n", config->textures->east->buff);
	// 	exit_with_error("Failed to load east texture\n", 1);
	// }

	// if ((game->textures->west->img_ptr = mlx_xpm_file_to_image(game->mlx, config->textures->west->buff,
	// 															&game->textures->west->width, &game->textures->west->height)) == NULL)
	// {
	// 	printf("Failed to load west texture: %s\n", config->textures->west->buff);
	// 	exit_with_error("Failed to load west texture\n", 1);
	// }

	if (config->textures->floor->buff)
	{
		if ((game->textures->floor->img_ptr = mlx_xpm_file_to_image(game->mlx, config->textures->floor->buff,
																  &game->textures->floor->width, &game->textures->floor->height)) == NULL)
			exit_with_error("Failed to load floor textures\n", 1);
	}
	else
		game->floor_color = config->floor_color; // Assign RGB floor color

	if (config->textures->ceiling->buff)
	{
		if ((game->textures->ceiling->img_ptr = mlx_xpm_file_to_image(game->mlx, config->textures->ceiling->buff,
																	&game->textures->ceiling->width, &game->textures->ceiling->height)) == NULL)
			exit_with_error("Failed to load ceiling textures\n", 1);
	}
	else
		game->ceiling_color = config->ceiling_color;

	// if (config->textures->door->buff)
	// {
	// 	if ((game->textures->door->img_ptr = mlx_xpm_file_to_image(game->mlx, config->textures->door->buff,
	// 															 &game->textures->door.width, &game->textures->door.height)) == NULL)
	// 	exit_with_error("Failed to load door textures\n", 1);
	// }

	return (0);
}
