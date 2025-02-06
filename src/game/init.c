#include "../../include/cub3d.h"

t_vector *init_vector(double x, double y)
{
	t_vector *vector = (t_vector *)malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	return (vector);
}

t_player *init_player(double x, double y, char NSEW)
{
	t_player *player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);

	if (!init_pos_dir_plane(player, NSEW, x, y))
	{
		free(player); // Free `player` before returning NULL
		return (NULL);
	}

	player->move_speed = 0.1;
	player->rot_speed = 0.1;
	player->health = 100;
	return (player);
}

int init_pos_dir_plane(t_player *player, char NSEW, double x, double y)
{
	player->pos = init_vector(x + 0.5, y + 0.5);
	if (!player->pos)
		return (0); // Return failure if `player->pos` allocation fails

	if (NSEW == 'E')
	{
		player->dir = init_vector(1.0, 0.0);
		player->plane = init_vector(0.0, 0.66);
	}
	else if (NSEW == 'W')
	{
		player->dir = init_vector(-1.0, 0.0);
		player->plane = init_vector(0.0, -0.66);
	}
	else if (NSEW == 'N')
	{
		player->dir = init_vector(0.0, -1.0);
		player->plane = init_vector(0.66, 0.0);
	}
	else if (NSEW == 'S')
	{
		player->dir = init_vector(0.0, 1.0);
		player->plane = init_vector(-0.66, 0.0);
	}
	else
	{
		free(player->pos); // Free `player->pos` if an invalid NSEW direction is given
		return (0);
	}

	// Check if `dir` or `plane` allocation failed
	if (!player->dir || !player->plane)
	{
		free(player->pos);
		if (player->dir)
			free(player->dir);
		if (player->plane)
			free(player->plane);
		return (0);
	}

	return (1);
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
		exit_with_error("Error loading textures", 1);
	textures->east = init_t_image();
	if (!textures->east)
		exit_with_error("Error loading textures", 1);
	textures->south = init_t_image();
	if (!textures->south)
		exit_with_error("Error loading textures", 1);
	textures->west = init_t_image();
	if (!textures->west)
		exit_with_error("Error loading textures", 1);
	textures->floor = init_t_image();
	if (!textures->floor)
		exit_with_error("Error loading textures", 1);
	textures->ceiling = init_t_image();
	if (!textures->ceiling)
		exit_with_error("Error loading textures", 1);
	textures->door = init_t_image();
	if (!textures->door)
		exit_with_error("Error loading textures", 1);
	textures->gameover = init_t_image();
	if (!textures->gameover)
		exit_with_error("Error loading textures", 1);
	//improvements still to be made, in case one fails we need to free the others that were allocated before
}

t_config *init_config(void)
{
	t_config *config;

	config = (t_config *)malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	config->map = (t_map *)malloc(sizeof(t_map));
	config->textures = (t_textures *)malloc(sizeof(t_textures));
	config->player = init_player(0, 0, 'N');

	init_textures(config->textures);
	config->ceiling_color = malloc(3 * sizeof(int));
	if (!config->ceiling_color)
		exit_with_error("Memory allocation failed", 0);
	config->floor_color = malloc(3 * sizeof(int));
	if (!config->floor_color)
		exit_with_error("Memory allocation failed", 0);
	return (config);
}

t_game *init_game(t_config *config)
{
	t_game *game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx_init();
	if (game->mlx == NULL) {
		exit_with_error("MLX initialization failed\n", 1);
	}
	game->screen_data = malloc(sizeof(int) * WIN_WIDTH * WIN_HEIGHT);
	if (!game->screen_data)
	{
		fprintf(stderr, "Error: Failed to allocate screen buffer\n");
		exit(1);
	}
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
    game->screen_data = (int *)mlx_get_data_addr(game->img, &game->bpp, &game->line_length, &game->endian);
	game->win = NULL;
	game->config = config;
	game->player = config->player;
	game->map = config->map;
	game->textures = config->textures;
	game->floor_color = config->floor_color;
	game->ceiling_color = config->ceiling_color;
	return (game);
}

// t_ray	*init_ray(void)
// {
// 	t_ray	*ray;

// 	ray = malloc(sizeof(t_ray));
// 	if (!ray)
// 		return (NULL);
// 	ray->dist = 0.0;
// 	ray->hit = NULL;
// 	ray->side = 0;
// 	ray->tex_x = 0;
// 	ray->lineHeight = 0.0;
// 	return (ray);
// }
