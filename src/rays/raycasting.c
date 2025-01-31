#include "../../include/cub3d.h"

/* Each ray’s direction is determined using this formula:

rayDirX = dirX + planeX × cameraX
rayDirY = dirY + planeY × camera X

  Where :

	dirX, dirY → Player’s view direction(where they’re looking).
	planeX, planeY → Camera plane(controls FOV).
	cameraX → Position of the column relative to the center of the screen.

The cameraX value determines how far left or right a ray is cast.

The center of the screen has cameraX = 0.
The leftmost pixel has cameraX = -1.
The rightmost pixel has cameraX = 1.
The formula for cameraX is:

cameraX = 2 × (column / screenWidth) - 1

This ensures:

cameraX = -1 at leftmost column.
cameraX = 0 at center column.
cameraX = 1 at rightmost column.

*/
void raycasting(void)
{
	int		x;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;

	x = 0;
	while (x < WIN_WIDTH)
	{
		// Calculate camera space X for this column (from -1 to 1)
		cameraX = 2 * (double)x / WIN_WIDTH - 1;

		// Calculate the ray direction based on the player's direction and the camera plane
		rayDirX = player->dir->x + player->plane->x * cameraX;
		rayDirY = player->dir->y + player->plane->y * cameraX;

		// Move to the next column
		x++;
	}
}
