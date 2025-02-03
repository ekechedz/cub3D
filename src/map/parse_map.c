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
static char *trim_trailing_spaces(const char *line)
{
	int len = ft_strlen(line);

	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\n'))
		len--;

	if (len == 0)
		return ft_strdup("");

	return ft_substr(line, 0, len);
}

void parse_map_line(t_config *config, const char *line)
{
	if (!config->map)
	{
		config->map = malloc(sizeof(t_map));
		if (!config->map)
			exit_with_error("Failed to allocate memory for map", 1);
		config->map->height = 0;
		config->map->width = 0;
		config->map->grid = NULL;
	}
	char *clean_line = trim_trailing_spaces(line);
	char **new_grid = realloc(config->map->grid, sizeof(char *) * (config->map->height + 1));
	if (!new_grid)
		exit_with_error("Failed to reallocate memory for map grid", 1);
	config->map->grid = new_grid;

	int line_length = ft_strlen(clean_line);
	if (line_length > config->map->width)
		config->map->width = line_length;
	config->map->grid[config->map->height] = clean_line;
	config->map->height++;

	printf("Parsed map line [%d]: %s\n", config->map->height, config->map->grid[config->map->height - 1]);
}

static int key_already_used(const char *key, char *used_keys[MAX_KEYS])
{
	int i;

	i = 0;
	while(i < MAX_KEYS)
	{
		if (used_keys[i] && strcmp(used_keys[i], key) == 0)
			return 1;
		i++;
	}
	return 0;
}

static void add_used_key(const char *key, char *used_keys[MAX_KEYS])
{
	int i;

	i = 0;
	while(i < MAX_KEYS)
	{
		if (!used_keys[i])
		{
			used_keys[i] = ft_strdup(key);
			return;
		}
		i++;
	}
}

static void parse_line(t_config *config, const char *line)
{
	static char *used_keys[MAX_KEYS] = {0};

	if (*line == '\0' || *line == '\n')
		return;

	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (key_already_used("NO", used_keys))
			exit_with_error("Error: Duplicate 'NO' texture", 1);
		config->textures->north->img_ptr = ft_strdup(line + 3);
		add_used_key("NO", used_keys);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (key_already_used("SO", used_keys))
			exit_with_error("Error: Duplicate 'SO' texture", 1);
		config->textures->south->img_ptr = ft_strdup(line + 3);
		add_used_key("SO", used_keys);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (key_already_used("WE", used_keys))
			exit_with_error("Error: Duplicate 'WE' texture", 1);
		config->textures->west->img_ptr = ft_strdup(line + 3);
		add_used_key("WE", used_keys);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (key_already_used("EA", used_keys))
			exit_with_error("Error: Duplicate 'EA' texture", 1);
		config->textures->east->img_ptr = ft_strdup(line + 3);
		add_used_key("EA", used_keys);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (key_already_used("F", used_keys))
			exit_with_error("Error: Duplicate 'F' floor color", 1);
		parse_color(line + 2, &config->floor_color);
		add_used_key("F", used_keys);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (key_already_used("C", used_keys))
			exit_with_error("Error: Duplicate 'C' ceiling color", 1);
		parse_color(line + 2, &config->ceiling_color);
		add_used_key("C", used_keys);
	}
	else
	{
		parse_map_line(config, line);
	}
}

static void normalize_map_width(t_config *config)
{
	for (int i = 0; i < config->map->height; i++)
	{
		int line_length = ft_strlen(config->map->grid[i]);
		if (line_length < config->map->width)
		{
			char *padded_line = malloc(config->map->width + 1);
			if (!padded_line)
				exit_with_error("Memory allocation failed for padding", 1);
			ft_strcpy(padded_line, config->map->grid[i]);
			ft_memset(padded_line + line_length, ' ', config->map->width - line_length);
			padded_line[config->map->width] = '\0';

			free(config->map->grid[i]);
			config->map->grid[i] = padded_line;
		}
	}
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
	if (config->map)
		normalize_map_width(config);

	validate_map(config);
	if (!config->map || config->map->width <= 0 || config->map->height <= 0)
	{
		fprintf(stderr, "Error: Invalid map in .cub file\n");
		return NULL;
	}
	return config;
}
