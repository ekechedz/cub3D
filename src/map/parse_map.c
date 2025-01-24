#include "../../include/cub3d.h"

int parse_int(const char **str)
{
	int value = 0;
	while (**str && ft_isdigit(**str))
	{
		value = value * 10 + (**str - '0');
		(*str)++;
	}
	if (value < 0 || value > 255)
		exit_with_error("Inavalid color", 1);
	return value;
}

void parse_color(const char *str, int *color)
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
		exit_with_error("Error color format", 0);
}

void parse_map_line(t_config *config, const char *line)
{
	if (!config && !config->map && !config->map->grid)
	{
		config->map->grid = malloc(sizeof(char *));
		if (!config->map->grid)
			exit_with_error("Error alocating map", 0);
		config->map->width = ft_strlen(line);
		config->map->height = 0;
	}
	config->map->height++;
	printf("%d\n", config->map->height);
	config->map->grid = realloc(config->map->grid, sizeof(char *) * config->map->height);
	if (!config->map->grid)
		exit_with_error("Error reallocating map", 1);
	config->map->grid[config->map->height - 1] = ft_strdup(line);
}

void parse_line(t_config *config, const char *line)
{
	if (*line == '\0' || *line == '\n')
		return;
	if (ft_strncmp(line, "NO ", 3) == 0)
		config->textures.north.buff = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		config->textures.south.buff = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		config->textures.west.buff = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		config->textures.east.buff = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(line + 2, &config->floor_color);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(line + 2, &config->ceiling_color);
	else
		 parse_map_line(config, line);
}

t_config *parse_cub_file(const char *file_path, t_config *config)
{
	char *map_buffer = NULL;
	char *line = NULL;
	int fd = open(file_path, O_RDONLY);
	if (fd == -1)
		exit_with_error("Failed to open file", 0);
	while ((line = get_next_line(fd)))
	{
		if (*line != '\n')
		{
			parse_line(config, line);
			size_t old_size;
			if (map_buffer)
				old_size = ft_strlen(map_buffer);
			else
				old_size = 0;
			size_t new_size = old_size + ft_strlen(line) + 2;
			if (map_buffer)
			{
				map_buffer = realloc(map_buffer, new_size);
				if (!map_buffer)
					exit_with_error("Failed to allocate memory", 0);
			}
			else
			{
				map_buffer = malloc(new_size);
				if (!map_buffer)
					exit_with_error("Failed to allocate memory", 0);
			}
			if (old_size > 0)
                map_buffer[old_size] = '\0';
			ft_strcat(map_buffer, line);
		}
		free(line);
	}
	close(fd);
	finalize_map(config, map_buffer);
	//free(map_buffer);
	return config;
}
