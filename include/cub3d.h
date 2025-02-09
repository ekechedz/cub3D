#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
//#include "/home/ekechedz/minilibx/mlx.h"
#include "/home/natalia/Repositories/minilibx/mlx.h"
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include "X11/Xlib.h"
#include "X11/keysym.h"
#include <sys/time.h>


// Constants
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MOVE_SPEED 0.5
#define ROT_SPEED 5
#define FOV 66
#define MAX_DEPTH 20.0
#define M_PI 3.14159265358979323846
#define MINI_SIZE 250
#define TILE_SIZE 40
#define CUBE_SIZE 64
#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64
#define MINI_MAP_SCALE 1

//move
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_ESC 53
#define KEY_COUNT 65536


// Map Characters
#define EMPTY '0'
#define WALL '1'
#define PLAYER_N 'N' //are you using this?
#define PLAYER_S 'S'
#define PLAYER_E 'E'
#define PLAYER_W 'W'
#define MAX_KEYS 6

#define ERROR "Memory problem"
#define M_ERROR "Map problem"

// Structs
typedef struct s_vector
{
	double x;
	double y;
} t_vector;

typedef struct s_player {
	t_vector    *pos;
	t_vector    *dir;
	t_vector    *plane;
	double      move_speed;  // Movement speed -- why do we need this if you already defined it it line 20
	double      rot_speed;   // Rotation speed -- same
	int         health;      // Player health
} t_player;

typedef struct s_image
{
	void *img_ptr;
	char *buff;
	int lstsize;
	int				bpp;
	int				endian;
	int width;
	int height;
	int line_length;
} t_image;

typedef struct s_textures
{
	t_image *north;
	t_image *east;
	t_image *south;
	t_image *west;
	t_image *floor;
	t_image *ceiling;
	t_image *door;
	t_image *gameover;
} t_textures;



typedef struct s_map
{
	char **grid; // 2D map array
	int width;
	int height;
} t_map;

typedef struct s_config {
    t_map       *map;        // Map structure
    t_textures  *textures;    // Textures for walls, floor, ceiling
    int         *floor_color; // Floor color (RGB)
    int         *ceiling_color; // Ceiling color (RGB)
    t_player    *player;      // Player settings (position, direction, etc.)
} t_config;



typedef struct s_game {
	void        *mlx;        // MiniLibX connection
	void        *win;        // MiniLibX window
	t_config    *config;     // Pointer to the game's configuration
	t_player    *player;     // Pointer to the player data
	t_map       *map;        // Pointer to the map structure
	int         *floor_color; // Floor color (RGB)
	int         *ceiling_color; // Ceiling color (RGB)
	t_textures  *textures;    // Game textures (walls, etc.)
	int *screen_data;  // Make sure it's modifiable
	void		*img;
	void		*addr;
	int     bpp;
	int     line_length;
	int     endian;
	struct timeval last_time;
	int      key_st[KEY_COUNT];  // Array to store key states (now inside the game struct)

} t_game;

typedef struct s_ray
{
    double dist;          // Distance to the wall
    t_vector *hit;        // Exact hit position on the wall
    int side;             // Which side of the wall was hit (0 = vertical, 1 = horizontal)
    int tex_x;            // X-coordinate on the texture
    int lineHeight;    // Height of the line to draw (based on distance to the wall)
    int drawStart;        // Y-coordinate to start drawing (top of the wall)
    int drawEnd;          // Y-coordinate to end drawing (bottom of the wall)
    double dirX;          // Direction vector X component
    double dirY;          // Direction vector Y component
    double deltaDistX;    // Change in distance for each step along the X axis
    double deltaDistY;    // Change in distance for each step along the Y axis
    double stepX;         // Step along the X axis (either 1 or -1, depending on direction)
    double stepY;         // Step along the Y axis (either 1 or -1, depending on direction)
    double sideDistX;     // Distance to the next vertical grid line
    double sideDistY;     // Distance to the next horizontal grid line
    double posX;          // Ray's starting X position
    double posY;          // Ray's starting Y position
    double perpWallDist;  // Perpendicular distance to the wall
    double cameraX;       // X-coordinate of the ray's camera position (for screen mapping)
    double texPos;        // Position of the texture on the wall for texture mapping
    double step;          // Amount to move through the texture
	int texX;
	double rayDirX;   // Ray's X direction component
    double rayDirY;   // Ray's Y direction component
} t_ray;


//Init functions
int main_loop(t_game *game);
int key_hook(int keycode, t_game *game);
int key_release_hook(int keycode, t_game *game);
void rotate_player(t_player *player, int direction, double delta_time);
void move_player(t_game *game, int direction, double delta_time);
void strafe_player(t_game *game, int direction, double delta_time);
t_config	*init_config(void);
t_image		*init_t_image(void);
t_vector	*init_vector(double x, double y);
int			init_pos_dir_plane(t_player *player, char NSEW, double x, double y);
t_map		*init_map(int width, int height);
t_player	*init_player(double x, double i, char NSEW);
t_game *init_game(t_config *config);
t_ray	*init_ray(void);
void	render(t_game *game);
void render_minimap(void *mlx, void *win, t_config *config);


// Function Prototypes
void	parse_map(const char *file, t_game *game);
int render_frame(t_game *game);
void	handle_input(int key, t_game *game);
void	cleanup(t_game *game);
int		render_frame_wrapper(void *param);
int		handle_input_wrapper(int key, void *param);
void draw_floor_ceiling(t_game *game);

// Validating map

//void validate_map(t_config *config);
void validate_map(t_map *map, t_config *config);
void exit_with_error(const char *message, int use_perror);
t_config *parse_cub_file(const char *file_path, t_config *config);

// Utils
void *ft_realloc(void *ptr, size_t old_size, size_t new_size);
char *ft_strncpy(char *dest, const char *src, size_t n);

// free
void	free_config(t_config *config);
int		free_player(t_player *player);

// textures
int load_textures(t_game *game, t_config *cfg);
void trim_whitespace(char *str);
t_image	*choose_texture(t_ray *ray, t_game *game);
int	get_txt_color(t_image *txt, int x, int y);

//render

int	render_slice(t_ray *ray, int texX, int x, t_game *game);
void render_texture(t_game *game, t_ray *ray, int x);

//rays

t_ray	*cast_rays(t_game *game);

#endif
