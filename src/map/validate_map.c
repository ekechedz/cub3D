#include "../../include/cub3d.h"

void validate_map(char **map)
{
	int i = 0;
	int player_count = 0;
	while (map[i])
	{
		int j = 0;
		while (map[i][j])
		{
			char c = map[i][j];
			if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' &&
				c != 'W' && c != ' ')
				exit_with_error("Invalid character in map.", 1);
			if ((c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W') &&
				(i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1] ||
				 map[i - 1][j] == ' ' || map[i + 1][j] == ' ' ||
				 map[i][j - 1] == ' ' || map[i][j + 1] == ' '))
				exit_with_error("Map is not surrounded by walls.", 1);
			j++;
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player_count++;
		}
		i++;
	}
	if (player_count != 1)
		exit_with_error("Map must contain exactly one player.", 1);
}
