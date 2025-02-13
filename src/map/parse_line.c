/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:27:28 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/13 15:33:01 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_empty_or_map_started(const char *line, int map_started)
{
	if (map_started == 0)
	{
		if (*line == '\0' || *line == '\n')
			return (1);
	}
	else
	{
		if (*line == '\0')
			return (1);
	}
	return (0);
}

void	parse_color_line(t_config *config, const char *line, \
	char *used_keys[MAX_KEYS])
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (key_already_used("F", used_keys))
			error("Error: Duplicate 'F' floor color", 1);
		parse_color(line + 2, config->floor_color);
		add_used_key("F", used_keys);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (key_already_used("C", used_keys))
			error("Error: Duplicate 'C' ceiling color", 1);
		parse_color(line + 2, config->ceiling_color);
		add_used_key("C", used_keys);
	}
}

void	parse_north_south_texture(t_config *config, const char *line, \
	char *used_keys[MAX_KEYS])
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (key_already_used("NO", used_keys))
			error("Error: Duplicate 'NO' texture", 1);
		config->textures->north->img_ptr = ft_strdup(line + 3);
		add_used_key("NO", used_keys);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (key_already_used("SO", used_keys))
			error("Error: Duplicate 'SO' texture", 1);
		config->textures->south->img_ptr = ft_strdup(line + 3);
		add_used_key("SO", used_keys);
	}
}

void	parse_west_east_texture(t_config *config, const char *line, \
	char *used_keys[MAX_KEYS])
{
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (key_already_used("WE", used_keys))
			error("Error: Duplicate 'WE' texture", 1);
		config->textures->west->img_ptr = ft_strdup(line + 3);
		add_used_key("WE", used_keys);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (key_already_used("EA", used_keys))
			error("Error: Duplicate 'EA' texture", 1);
		config->textures->east->img_ptr = ft_strdup(line + 3);
		add_used_key("EA", used_keys);
	}
}

void	parse_texture_line(t_config *config, const char *line, \
	char *used_keys[MAX_KEYS])
{
	parse_north_south_texture(config, line, used_keys);
	parse_west_east_texture(config, line, used_keys);
}
