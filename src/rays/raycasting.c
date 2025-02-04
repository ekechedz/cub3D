#include "../../include/cub3d.h"
#include <float.h>

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
#include <float.h>
#include <stdio.h>

t_ray *raycasting(t_game *game)
{
	int x;
	double cameraX, rayDirX, rayDirY;
	double deltaDistX, deltaDistY;
	double sideDistX, sideDistY;
	int mapX, mapY;
	int stepX, stepY;
	int hit, side;
	char **map = game->map->grid;

	t_ray *rays = malloc(sizeof(t_ray) * WIN_WIDTH);
	if (!rays)
	{
		fprintf(stderr, "Memory allocation failed for rays\n");
		exit(EXIT_FAILURE);
	}

	printf("Player starting position: (%f, %f)\n", game->player->pos->x, game->player->pos->y);

	for (x = 0; x < WIN_WIDTH; x++)
	{
		t_ray *ray = &rays[x];
		ray->hit = init_vector(0, 0);
		hit = 0;

		cameraX = 2 * (double)x / WIN_WIDTH - 1;
		rayDirX = game->player->dir->x + game->player->plane->x * cameraX;
		rayDirY = game->player->dir->y + game->player->plane->y * cameraX;

		//printf("\nColumn %d: cameraX = %f, rayDirX = %f, rayDirY = %f\n", x, cameraX, rayDirX, rayDirY);

		mapX = (int)game->player->pos->x;
		mapY = (int)game->player->pos->y;

		//printf("Starting grid cell: (%d, %d)\n", mapX, mapY);
	// Calculate delta distance (steps for each direction)
		deltaDistX = fabs(1 / rayDirX); // step size in the X direction
		deltaDistY = fabs(1 / rayDirY); // step size in the Y direction

	// Determine which direction we should step
		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (game->player->pos->x - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player->pos->x) * deltaDistX;
		}

		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (game->player->pos->y - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player->pos->y) * deltaDistY;
		}


		//printf("StepX: %d, StepY: %d, SideDistX: %f, SideDistY: %f\n", stepX, stepY, sideDistX, sideDistY);

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			//printf("Stepping to: (%d, %d), side = %d\n", mapX, mapY, side);

			if (mapX < 0 || mapX >= game->map->width || mapY < 0 || mapY >= game->map->height)
			{
				hit = 1;
				printf("Ray out of bounds at: (%d, %d)\n", mapX, mapY);
				break;
			}

			if (map[mapX][mapY] == '1')
			{
				hit = 1;
				//printf("Wall hit at: (%d, %d)\n", mapX, mapY);
			}
		}

		double perpWallDist = (side == 0) ? (sideDistX - deltaDistX) : (sideDistY - deltaDistY);
		//printf("Perpendicular Wall Distance: %f\n", perpWallDist);

		ray->dist = perpWallDist;
		ray->hit->x = mapX;
		ray->hit->y = mapY;
		ray->side = side;

		double wallX;
		if (side == 0)
			wallX = game->player->pos->y + perpWallDist * rayDirY;
		else
			wallX = game->player->pos->x + perpWallDist * rayDirX;

		wallX -= floor(wallX); // Get the fractional part of wall hit position

		int texWidth = 64;
		ray->tex_x = (int)(wallX * (double)texWidth);

		// Flip texture if necessary
		if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
			ray->tex_x = texWidth - ray->tex_x - 1;

		//printf("Texture X coordinate: %d\n", ray->tex_x);

		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;

		if (drawStart < 0)
			drawStart = 0;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		//printf("Draw Range: Start = %d, End = %d, Line Height = %d\n", drawStart, drawEnd, lineHeight);
	}

	return rays;
}

// 6. How to Proceed (Drawing the Line)

// To render the raycast results to the screen, you need to:

//     Use your graphics library (such as SDL, or whatever you're using) to draw the wall slice.
//     Loop through all the rays and draw them with the drawStart and drawEnd values.

// Here's a basic structure to draw the line in a graphics window:

// for (x = 0; x < WIN_WIDTH; x++) {
//     // 1. Camera transformation and ray direction calculation as before...

//     // 2. DDA loop to find where the ray hits a wall

//     // 3. Perpendicular distance and wall height calculation

//     // 4. Drawing the vertical line for the ray:
//     int color = getWallColor(side);  // You can color walls differently depending on side
//     for (int y = drawStart; y < drawEnd; y++) {
//         drawPixel(x, y, color);  // Draw pixel at (x, y) with the appropriate color
//     }
// }

//     getWallColor(side) can vary the color depending on which side (X or Y) the ray hits.
//     drawPixel(x, y, color) would be your graphics API function for drawing a pixel.

// Final Steps:

//     Integrate this rendering code into your game loop where you handle the screen buffer.
//     Test your raycasting with simple maps and ensure the walls are drawn correctly.
//     Adjust the FOV and other parameters to refine the visual effect.
