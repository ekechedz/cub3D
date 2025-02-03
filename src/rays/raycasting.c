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
void raycasting(t_player *player, t_game *game)
{
	int x;
	double cameraX, rayDirX, rayDirY;
	double deltaDistX, deltaDistY;
	double sideDistX, sideDistY;
	int mapX, mapY;
	int stepX, stepY;
	int hit = 0;
	int side; // 0 for x-axis, 1 for y-axis
	char **map = game->map->grid; //for now

	// Loop through all columns on the screen
	for (x = 0; x < WIN_WIDTH; x++) 
	{
		// 1. Calculate camera space X for this column
		cameraX = 2 * (double)x / WIN_WIDTH - 1;
		rayDirX = player->dir->x + player->plane->x * cameraX;
		rayDirY = player->dir->y + player->plane->y * cameraX;

		// 2. Initialize DDA variables
		// Initial map position (current grid cell)
		mapX = (int)player->pos->x;
		mapY = (int)player->pos->y;

		// Calculate the deltaDistX and deltaDistY
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);

		// Calculate step and sideDist
		if (rayDirX < 0) 
		{
			stepX = -1;
			sideDistX = (player->pos->x - mapX) * deltaDistX;
		}
		else 
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->pos->x) * deltaDistX;
		}
		
		if (rayDirY < 0) 
		{
			stepY = -1;
			sideDistY = (player->pos->y - mapY) * deltaDistY;
		}
		else 
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player->pos->y) * deltaDistY;
		}

		// 3. DDA loop to step through grid cells until a wall is hit
		while (hit == 0)
		{
			// Move to the next grid cell
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

			// Check if we've hit a wall
			if (map[mapX][mapY] == '1')  // Wall is represented by '1'
				hit = 1;
		}

		// 4. Calculate the distance to the wall and draw the line
		double perpWallDist;
		if (side == 0) 
			perpWallDist = (sideDistX - deltaDistX);  // Distance along the X-axis
		else 
			perpWallDist = (sideDistY - deltaDistY);  // Distance along the Y-axis

		// Draw the vertical line corresponding to this ray
		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;

		// Ensure we don't draw out of bounds
		if (drawStart < 0) drawStart = 0;
		if (drawEnd >= WIN_HEIGHT) drawEnd = WIN_HEIGHT - 1;

		// Now you can draw the line here with `drawStart` and `drawEnd` 
		// You can use these to color the line based on the wall type
	}
}

6. How to Proceed (Drawing the Line)

To render the raycast results to the screen, you need to:

    Use your graphics library (such as SDL, or whatever you're using) to draw the wall slice.
    Loop through all the rays and draw them with the drawStart and drawEnd values.

Here's a basic structure to draw the line in a graphics window:

for (x = 0; x < WIN_WIDTH; x++) {
    // 1. Camera transformation and ray direction calculation as before...
    
    // 2. DDA loop to find where the ray hits a wall
    
    // 3. Perpendicular distance and wall height calculation
    
    // 4. Drawing the vertical line for the ray:
    int color = getWallColor(side);  // You can color walls differently depending on side
    for (int y = drawStart; y < drawEnd; y++) {
        drawPixel(x, y, color);  // Draw pixel at (x, y) with the appropriate color
    }
}

    getWallColor(side) can vary the color depending on which side (X or Y) the ray hits.
    drawPixel(x, y, color) would be your graphics API function for drawing a pixel.

Final Steps:

    Integrate this rendering code into your game loop where you handle the screen buffer.
    Test your raycasting with simple maps and ensure the walls are drawn correctly.
    Adjust the FOV and other parameters to refine the visual effect.