#include "../../include/cub3d.h"

void calculate_map_dimensions(char *map_buffer, size_t *map_height, size_t *map_width)
{
	if (!map_buffer)
		exit_with_error("Map buffer is NULL", 0);
	*map_height = 0;
	*map_width = 0;
	size_t i;
	i = 0;
	while (map_buffer[i] != '\0')
	{
		if (map_buffer[i] == '\n')
			(*map_height)++;
		else if (*map_height == 0)
			(*map_width)++;
		else if (map_buffer[i - 1] == '\n')
			*map_width = 0;
		i++;
	}
}

void populate_map_grid(t_config *config, char *map_buffer, size_t map_height)
{
	if (!map_buffer)
		exit_with_error("Map buffer is NULL", 0);
	config->map->grid = malloc(sizeof(char *) * (map_height + 1));
	if (!config->map->grid)
		exit_with_error("Failed to allocate memory for map grid", 0);
	size_t row;
	row = 0;
	char *line_start = map_buffer;
	size_t i = 0;
	while (map_buffer[i] != '\0')
	{
		if (map_buffer[i] == '\n' || map_buffer[i + 1] == '\0')
		{
			size_t line_length = &map_buffer[i] - line_start;
			config->map->grid[row] = malloc(line_length + 1);
			if (!config->map->grid[row])
				exit_with_error("Failed to allocate memory for map line", 0);
			ft_strncpy(config->map->grid[row], line_start, line_length);
			config->map->grid[row][line_length] = '\0';
			row++;
			line_start = &map_buffer[i + 1];
		}
		i++;
	}
}

void finalize_map(t_config *config, char *map_buffer)
{
	size_t map_height = 0;
	size_t map_width = 0;

	calculate_map_dimensions(map_buffer, &map_height, &map_width);
	populate_map_grid(config, map_buffer, map_height);

	validate_map(config->map->grid);
	config->map->width = map_width;
	config->map->height = map_height;
	printf("are you getting out herre");
}
