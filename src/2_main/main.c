#include "../../libft/libft.h"
#include "../../include/cub3d.h"

char	*check_file(char *filename)
{
	int	len;
	int	i;

	len = ft_strlen(filename);
	i = fmax(len - 5, 0);
	while (filename[i] != '.' && filename[i] != '\0')
		i++;
	return (filename + i);
}

int	check_input(int ac, char **av)
{
	if (ac != 2 || ft_strncmp(check_file(av[1]), ".cub", 5) != 0)
	{
		ft_putendl_fd("Usage: ./cub3d file.cub", 2);
		exit (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game		*game;
	t_config	*config;

	check_input(argc, argv);
	config = init_config();
	if (!config)
		error("Failed to initialize configuration\n", 1);
	if (!parse_cub_file(argv[1], config)) //in case of error, i already free config inside
		error("Failed to parse .cub file\n", 1);
	game = init_game(config);
	if (!game)
		error("Failed to initialize game\n", 1);
	if (load_textures(game, config) < 0)
	{
		fprintf(stderr, "Error: Failed to load textures\n");
		free_game(game);
		return (1);
	}
	init_events(game);
	mlx_loop(game->mlx);
	cleanup_all(game, config);
	return (0);
}

