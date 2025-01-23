#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <string.h>
# include "/home/ekechedz/minilibx/mlx.h"
# include "X11/Xlib.h"
# include "X11/keysym.h"

// Constants
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MOVE_SPEED 0.05
#define ROT_SPEED 0.03
#define FOV 66
#define MAX_DEPTH 20.0

// Map Characters
#define EMPTY '0'
#define WALL '1'
#define PLAYER_N 'N'
#define PLAYER_S 'S'
#define PLAYER_E 'E'
#define PLAYER_W 'W'
#define ERROR "Memory problem"
#define M_ERROR "Map problem"

// Structs
typedef struct s_vector
{
    double x;
    double y;
} t_vector;

typedef struct s_player
{
    t_vector pos;
    t_vector dir;
	int 	health;
} t_player;

typedef struct s_image
{
	void			*img_ptr;
	char			*buff;
	int				lstsize;
	int				width;
	int				height;
}					t_image;

typedef struct s_textures
{
	t_image			north;
	t_image			east;
	t_image			south;
	t_image			west;
	t_image			floor;
	t_image			ceiling;
	t_image			door;
	t_image			gameover;
}					t_textures;


typedef struct s_map
{
    char **grid; // 2D map array
    int width;
    int height;
} t_map;

typedef struct s_game
{
    void *mlx;         // MiniLibX instance
    void *win;         // Window instance
    t_player player;   // Player data
    t_map map;         // Map data
    int floor_color;   // Floor color (RGB)
    int ceiling_color; // Ceiling color (RGB)
} t_game;

// Function Prototypes
void init_game(t_game *game);
void parse_map(const char *file, t_game *game);
void render_frame(t_game *game);
void handle_input(int key, t_game *game);
void cleanup(t_game *game);
int render_frame_wrapper(void *param);
int handle_input_wrapper(int key, void *param);

#endif
