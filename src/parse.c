#include "include/cub3d.h"

void parse_map(const char *file, t_game *game)
{
    int fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening map file");
        exit(1);
    }

    // Temporary: Load a hardcoded map
    static char *temp_map[] = {
        "11111",
        "10001",
        "10001",
        "1N001",
        "11111",
        NULL};

    game->map.grid = temp_map;
    game->map.width = 5;
    game->map.height = 5;

    close(fd);
}
