/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:53:44 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/17 14:31:58 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	parse_int(const char **str)
{
	int	num;

	num = 0;
	while (**str == ' ')
		(*str)++;
	if (!ft_isdigit(**str))
		error("Invalid number in color format", 0, NULL, NULL);
	while (**str && ft_isdigit(**str))
	{
		num = num * 10 + (**str - '0');
		(*str)++;
	}
	return (num);
}

int	parse_color(const char *str, int *color)
{
	int	i;
	int	component;

	i = 0;
	if (!color)
		error("Null color pointer", 0, NULL, NULL);
	while (*str && i < 3)
	{
		component = parse_single_color_component(&str);
		if (component == -1)
			return (0);
		color[i] = component;
		i++;
		if (!check_and_skip_comma(&str))
			break ;
	}
	if (i != 3)
		return (0);
	while (*str == ' ')
		str++;
	if (*str != '\0' && *str != '\n')
		return (0);
	return (1);
}

void	*parse_map_line(t_config *config, char *line)
{
	char	*clean_line;

	clean_line = trim_trailing_spaces(line);
	if (!clean_line)
		return (NULL);
	if (validate_line(clean_line) == 0)
	{
		free(clean_line);
		free(line);
		error("Unexpected char in the map", 0, NULL, config);
	}
	process_map_line(config, clean_line);
	free(clean_line);
	return (config);
}

static int	parse_line(t_config *config, char *line)
{
	static int	map_started;

	if (is_empty_or_map_started(line, map_started))
		return (1);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 \
	|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		parse_texture_line(config, line);
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		parse_color_line(config, line);
	else
	{
		map_started = 1;
		if (!parse_map_line(config, line))
			return (0);
	}
	return (1);
}

t_config	*parse_cub_file(const char *file_path, t_config *config)
{
	char	*line;
	int		fd;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			if (!parse_line(config, line))
			{
				free(line);
				error("Error parsing map line", 0, NULL, config);
			}
			free(line);
		}
	}
	close(fd);
	validate_map(config->map, config);
	if (!config->map || config->map->width <= 0 || config->map->height <= 0)
		error("Invalid map in .cub file", 0, NULL, config);
	return (config);
}
