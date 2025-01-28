#include "../../include/cub3d.h"

static int parse_int(const char **str)
{
	int value = 0;

	while (**str && ft_isdigit(**str))
	{
		value = value * 10 + (**str - '0');
		(*str)++;
	}
	if (value < 0 || value > 255)
		exit_with_error("Invalid color value", 1);
	return value;
}

static void parse_color(const char *str, int *color)
{
	int i = 0;

	while (*str && i < 3)
	{
		while (*str == ' ')
			str++;
		color[i++] = parse_int(&str);
		if (*str == ',')
			str++;
	}
	if (i != 3)
		exit_with_error("Error in color format", 0);
}
void parse_map_line(t_config *config, const char *line)
{
    // Initialize the map if it hasn't been initialized yet
    if (!config->map)
    {
        config->map = malloc(sizeof(t_map));
        if (!config->map)
            exit_with_error("Failed to allocate memory for map", 1);

        config->map->height = 0;
        config->map->width = 0;
        config->map->grid = NULL;
    }

    config->map->height++;
    char **new_grid = realloc(config->map->grid, sizeof(char *) * config->map->height);
    if (!new_grid)
        exit_with_error("Failed to reallocate memory for map grid", 1);

    config->map->grid = new_grid;

    // Duplicate the line and add it to the grid
    config->map->grid[config->map->height - 1] = ft_strdup(line);
    if (!config->map->grid[config->map->height - 1])
        exit_with_error("Failed to duplicate map line", 1);

    // Update the map width to the longest line encountered
    int line_width = ft_strlen(line);
    if (line_width > config->map->width)
        config->map->width = line_width;
}



static void parse_line(t_config *config, const char *line)
{
	if (*line == '\0' || *line == '\n')
		return;

	if (ft_strncmp(line, "NO ", 3) == 0)
		config->textures->north->buff = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		config->textures->south->buff = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		config->textures->west->buff = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		config->textures->east->buff = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(line + 2, &config->floor_color);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(line + 2, &config->ceiling_color);
	else
		parse_map_line(config, line);
}

t_config *parse_cub_file(const char *file_path, t_config *config)
{
	char *line = NULL;
	int fd = open(file_path, O_RDONLY);

	if (fd == -1)
		exit_with_error("Failed to open .cub file", 0);

	while ((line = get_next_line(fd)))
	{
		parse_line(config, line);
		free(line);
	}
	close(fd);
	//finalize_map(config); // add it latter

	if (!config->map || config->map->width <= 0 || config->map->height <= 0)
    {
        fprintf(stderr, "Error: Invalid map in .cub file\n");
        return NULL;
    }
	return config;
}
