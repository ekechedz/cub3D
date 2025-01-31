#include "../../include/cub3d.h"

t_player *player init_player(double x, double i, char NSEW)
{
	player->pos = (t_vector *)malloc(sizeof(t_vector));
	player->dir = (t_vector *)malloc(sizeof(t_vector));
	player->plane = (t_vector *)malloc(sizeof(t_vector));

	player->pos->x = x + 0.5; //this 0.5 is so the player is in the middle of the tile
    player->pos->y = y + 0.5;
    player->dir->x = 0;
	player->dir->y = 0;
    if (NSEW == 'E')
        player->dir->x = 1;
    else if (NSEW == 'E')
        player->dir->x = -1;
    else if (NSEW == 'N')
        player->dir->y = -1;
    else if (NSEW == 'S')
        player->dir->x = 1;
    player->plane->x = 0;
	player->plane->y = 0.66;
	player->move_speed = 0.1;
	player->rot_speed = 0.1;
	player->health = 100;
    return (player);
}

t_map *init_map(int width, int height)
{
	t_map *map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		return NULL;
	map->width = width;
	map->height = height;
	map->grid = (char **)malloc(sizeof(char *) * height);
	if (map->grid == NULL)
	{
		free(map);
		return NULL;
	}
	for (int i = 0; i < height; i++)
	{
		map->grid[i] = (char *)malloc(sizeof(char) * (width + 1));
		if (map->grid[i] == NULL)
		{
			for (int j = 0; j < i; j++)
			{
				free(map->grid[j]);
			}
			free(map->grid);
			free(map);
			return NULL;
		}
		ft_memset(map->grid[i], 0, sizeof(char) * (width + 1));
	}
	return map;
}

// Function to initialize textures
void init_textures(t_textures *textures)
{
	textures->north = (t_image *)malloc(sizeof(t_image));
	textures->east = (t_image *)malloc(sizeof(t_image));
	textures->south = (t_image *)malloc(sizeof(t_image));
	textures->west = (t_image *)malloc(sizeof(t_image));
	textures->floor = (t_image *)malloc(sizeof(t_image));
	textures->ceiling = (t_image *)malloc(sizeof(t_image));
	textures->door = (t_image *)malloc(sizeof(t_image));
	textures->gameover = (t_image *)malloc(sizeof(t_image));

	textures->north->img_ptr = NULL;
	textures->north->buff = NULL;
	textures->north->lstsize = 0;
	textures->north->width = 0;
	textures->north->height = 0;

	textures->east->img_ptr = NULL;
	textures->east->buff = NULL;
	textures->east->lstsize = 0;
	textures->east->width = 0;
	textures->east->height = 0;

	textures->south->img_ptr = NULL;
	textures->south->buff = NULL;
	textures->south->lstsize = 0;
	textures->south->width = 0;
	textures->south->height = 0;

	textures->west->img_ptr = NULL;
	textures->west->buff = NULL;
	textures->west->lstsize = 0;
	textures->west->width = 0;
	textures->west->height = 0;

	textures->floor->img_ptr = NULL;
	textures->floor->buff = NULL;
	textures->floor->lstsize = 0;
	textures->floor->width = 0;
	textures->floor->height = 0;

	textures->ceiling->img_ptr = NULL;
	textures->ceiling->buff = NULL;
	textures->ceiling->lstsize = 0;
	textures->ceiling->width = 0;
	textures->ceiling->height = 0;
}

// Function to initialize config
void init_config(t_config *config)
{
	config->map = (t_map *)malloc(sizeof(t_map));
	config->textures = (t_textures *)malloc(sizeof(t_textures));
	init_player(&config->player);
	init_textures(config->textures);

	config->floor_color = 0x000000;	  // Default black
	config->ceiling_color = 0xFFFFFF; // Default white
}

// Function to initialize game
void init_game(t_game *game, t_config *config)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL) {
		exit_with_error("MLX initialization failed\n", 1);
	}
	game->win = NULL;		// Initialize window to NULL (we'll create it later)
	game->config = config;
	game->player = &config->player;
	game->map = config->map;
	game->textures = config->textures; // Set textures from config

	// You can initialize floor and ceiling color here as well
	game->floor_color = config->floor_color;
	game->ceiling_color = config->ceiling_color;
}
