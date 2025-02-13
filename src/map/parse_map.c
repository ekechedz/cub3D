/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:53:44 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/13 18:29:37 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/cub3d.h"

static int	parse_int(const char **str)
{
	int	num;

	num = 0;
	while (**str == ' ')
		(*str)++;
	if (!ft_isdigit(**str))
	{
		perror("Invalid number in color format"); //check it
		return (0);
	}
	while (**str && ft_isdigit(**str))
	{
		num = num * 10 + (**str - '0');
		(*str)++;
	}
	return (num);
}

void	parse_color(const char *str, int *color)
{
	int	i;

	i = 0;
	if (!color)
		perror("Null color pointer"); //check
	while (*str && i < 3)
	{
		while (*str == ' ')
			str++;
		if (!ft_isdigit(*str))
			perror("Invalid color format"); //check
		color[i] = parse_int(&str);
		if (color[i] < 0 || color[i] > 255)
			perror("RGB values must be between 0 and 255"); //check
		i++;
		while (*str == ' ')
			str++;
		if (*str == ',')
			str++;
	}
	if (i != 3)
		perror("Error in color format"); //check
}

void	*parse_map_line(t_config *config, const char *line)
{
	char	*clean_line;

	clean_line = trim_trailing_spaces(line);
	if (!validate_line(clean_line))
		return (free_config(config));
	process_map_line(config, clean_line); //check for errors
	free(clean_line);
	return (config);
}

static void	*parse_line(t_config *config, const char *line)
{
	static char	*used_keys[MAX_KEYS] = {0};
	static int	map_started;

	if (is_empty_or_map_started(line, map_started))
		return (config);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 \
	|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		parse_texture_line(config, line, used_keys);
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		parse_color_line(config, line, used_keys);
	else
	{
		map_started = 1;
		if (!parse_map_line(config, line))
			return (NULL);
	}
	return (config);
}

t_config	*parse_cub_file(const char *file_path, t_config *config)
{
	char	*line;
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (free_config(config));
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			if (!parse_line(config, line))
			{
				free(line);
				return (NULL);
			}
			free(line);
		}
	}
	close(fd);
	validate_map(config->map, config);
	if (!config->map || config->map->width <= 0 || config->map->height <= 0)
	{
		fprintf(stderr, "Error: Invalid map in .cub file\n");
		return (free_config(config));
	}
	return (config);
}
