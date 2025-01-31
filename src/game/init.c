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

t_image *init_t_image(void)
{
    t_image *new;

    new = malloc(sizeof(t_image));
    if (!new)
        return (NULL);
    new->img_ptr = NULL;
    new->buff = NULL;
    new->lstsize = 0;
    new->width = 0;
    new->height = 0;
    return (new);
}

void init_textures(t_textures *textures)
{
	textures->north = init_t_image();
    if (!textures->north)
        exit_with_error(1);
    textures->east = init_t_image();
    if (!textures->east)
        exit_with_error(1);
    textures->south = init_t_image();
    if (!textures->south)
        exit_with_error(1);
    textures->west = init_t_image();
    if (!textures->west)
        exit_with_error(1);
    textures->floor = init_t_image();
    if (!textures->floor)
        exit_with_error(1);
    textures->ceiling = init_t_image();
    if (!textures->ceiling)
        exit_with_error(1);
    textures->door = init_t_image();
    if (!textures->door)
        exit_with_error(1);
    textures->gameover = init_t_image();
    if (!textures->gameover)
        exit_with_error(1);
    //improvements still to be made, in case one fails we need to free the others that were allocated before
}

void init_config(t_config *config)
{
	config->map = (t_map *)malloc(sizeof(t_map));
	config->textures = (t_textures *)malloc(sizeof(t_textures));
	config->player = NULL; //initialize later, like described in issue #4
	init_textures(config->textures);

	config->floor_color = 0x000000;	  // Default black
	config->ceiling_color = 0xFFFFFF; // Default white
}

void init_game(t_game *game, t_config *config)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL) {
		exit_with_error("MLX initialization failed\n", 1);
	}
	game->win = NULL;
	game->config = config;
	game->player = &config->player;
	game->map = config->map;
	game->textures = config->textures;

	game->floor_color = config->floor_color;
	game->ceiling_color = config->ceiling_color;
}
