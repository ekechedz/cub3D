#include "../../include/cub3d.h"

t_vector	*init_vector(double x, double y)
{
	t_vector	*vector;
	
	vector = (t_vector *)malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	return (vector);
}

t_player *init_player(double x, double y)
{
	t_player	*player;
	
	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->pos = init_vector(x + 0.5, y + 0.5);
	if (!player->pos)
		return (free_player(player)); // Return failure if `player->pos` allocation fails
	player->move_speed = 0.1;
	player->rot_speed = 0.1;
	player->health = 100;
	return (player);
}

int	init_pos_dir_plane(t_player *player, char NSEW)
{
	if (NSEW == 'E')
	{
		player->dir = init_vector(1.0, 0.0);
		player->plane = init_vector(0.0, 0.66);
	}
	else if (NSEW == 'N')
	{
		player->dir = init_vector(-1.0, 0.0);
		player->plane = init_vector(0.0, -0.66);
	}
	else if (NSEW == 'W')
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
	printf("Player initialized at (%.2f, %.2f) facing dir(%.2f, %.2f) with plane(%.2f, %.2f)\n",
    player->pos->x, player->pos->y, player->dir->x, player->dir->y, player->plane->x, player->plane->y);

	return (1);
}

t_map *init_map(int width, int height)
{
	t_map *map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		return NULL;
	map->width = width; //this is always zero, why do we bother then
	map->height = height; //this is always zero, why do we bother then
	map->grid = (char **)malloc(sizeof(char *) * height);
	if (map->grid == NULL)
		return (free_map(map));
	for (int i = 0; i < height; i++)
	{
		//i dont think this is necessary because you already get an allocated line from gnl
		map->grid[i] = (char *)malloc(sizeof(char) * (width + 1));
		if (map->grid[i] == NULL)
			return (free_map(map));
		ft_memset(map->grid[i], 0, sizeof(char) * (width + 1));
	}
	return (map);
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

static t_textures	*init_textures(void)
{
	t_textures	*t;

	t = malloc(sizeof(t_textures));
	if (!t)
		return (NULL);
	t->north = init_t_image();
	t->east = init_t_image();
	t->south = init_t_image();
	t->west = init_t_image();
	t->floor = init_t_image();
	t->ceiling = init_t_image();
	if (!t->north || !t->east || !t->south || !t->west || !t->floor || !t->ceiling)
		return (free_textures(t));
	return (t);
}

t_config *init_config(void)
{
	t_config	*config;

	config = (t_config *)malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	config->map = init_map(0, 0);
	if (!config->map)
		return (free_config(config)); 
	config->textures = init_textures();
	if (!config->textures)
		return (free_config(config));
	//config->player = init_player(0, 0, 'N'); //hm
	config->ceiling_color = malloc(3 * sizeof(int));
	if (!config->ceiling_color)
		return (free_config(config));
	config->floor_color = malloc(3 * sizeof(int));
	if (!config->floor_color)
		return (free_config(config));
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

t_ray	*init_ray(void)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->dist = 0.0;
	ray->hit = NULL;
	ray->side = 0;
	ray->tex_x = 0;
	ray->lineHeight = 0.0;
	return (ray);
}
