#include "../../include/cub3d.h"

t_game *init_game(void)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		perror("Error initializing MiniLibX");
		exit(1);
	}

	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
	{
		perror("Error creating window");
		exit(1);
	}
	// game->floor_color = 0x00AA00;   // Green
	// game->ceiling_color = 0x0000FF; // Blue
	game->player = init_player(); //maybe we should initialize it in the map parsing
	game->map = init_map(); //maybe we should initialize it in the map parsing
	return (game);
}

t_config	*init_config(void)
{
	t_config *config;

	config = malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	ft_memset(config, 0, sizeof(t_config));
	config->map = malloc(sizeof(t_map));
	if (!config->map)
	{
		free(config);
		return (NULL);
	}
	return (config);
}

t_player *init_player(void)
{
	t_player *p;

	p = malloc(sizeof(t_player));
	if (!p)
	{
		printf("Error initializing player struct\n");
		return (NULL);
	}
	p->pos = init_vector(0,0);  //probably we want to pass player position as arg here
	if (!p->pos)
	{
		printf("Error initializing player position\n");
		free (p);
		return (NULL);
	}
	p->dir = init_vector(0,0); //probably the information of the map
	{
		printf("Error initializing player direction\n");
		free (p->pos);
		free (p);
		return (NULL);
	}
	p->health = 0;
	return (p);
}

t_vector	*init_vector(double x, double y)
{
	t_vector *v;

	v = malloc(sizeof(t_vector));
	if (!v)
		return (NULL);
	v->x = x;
	v->y = y;
	return (v);
}

t_map *init_map(void)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	if (!map)
	{
		printf("Error allocating map in init_map");
		return (NULL);
	}
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	return (map);
}


