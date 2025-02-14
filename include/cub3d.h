#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
//#include "/home/ekechedz/minilibx/mlx.h"
#include "/home/nleite-s/Repositories/cub3d/minilibx/mlx.h"
#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include "X11/Xlib.h"
#include "X11/keysym.h"
#include <sys/time.h>


// Constants
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MOVE_SPEED 2
#define ROT_SPEED 5
#define FOV 66
#define MAX_DEPTH 20.0
#define M_PI 3.14159265358979323846
#define MINI_SIZE 250
#define TILE_SIZE 40
#define CUBE_SIZE 64
#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64


//move
#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_ESC 53
#define KEY_COUNT 65536

// Mini map
#define MINIMAP_SCALE 10	// Scale for minimap (1 map unit = 10 pixels)
#define MINIMAP_X_OFFSET 20 // Minimap position on screen
#define MINIMAP_Y_OFFSET 20
#define PLAYER_COLOR 0xFF4500 // Red dot for player
#define WALL_COLOR 0x444444
#define FLOOR_COLOR 0x222222
#define EMPTY_COLOR 0x888888
#define RAY_COLOR 0x00FFAA // Yellow for view direction
#define PLAYER_RADIUS 3	   // Player indicator radius
#define RAY_LENGTH 100	   // Player's view ray length

// Map Characters
#define EMPTY '0'
#define WALL '1'
#define PLAYER_N 'N' //are you using this?
#define PLAYER_S 'S'
#define PLAYER_E 'E'
#define PLAYER_W 'W'
#define MAX_KEYS 6

//Draw constants
#define CEILING 1
#define FLOOR 2

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
} t_textures;



typedef struct s_map
{
	char **grid; // 2D map array
	int width;
	int height;
} t_map;

typedef struct s_config {
	t_map		*map;        // Map structure
	t_textures  *textures;    // Textures for walls, floor, ceiling
	int         *floor_color; // Floor color (RGB)
	int         *ceiling_color; // Ceiling color (RGB)
	t_player    *player;      // Player settings (position, direction, etc.)
	char	*used_keys[MAX_KEYS];
} t_config;



typedef struct s_game {
	void        *mlx;        // MiniLibX connection
	void        *win;        // MiniLibX window
	t_player    *player;     // Pointer to the player data
	t_map       *map;        // Pointer to the map structure
	int         *floor_color; // Floor color (RGB)
	int         *ceiling_color; // Ceiling color (RGB)
	t_textures  *textures;    // Game textures (walls, etc.)
	int *screen_data;  // Make sure it's modifiable
	void		*img;
	int     bpp;
	int     line_length;
	int     endian;
	struct timeval last_time;
	int      key_st[KEY_COUNT];
	t_config	*config;
} t_game;

typedef struct s_ray
{
	double dist;
	t_vector *hit;
	int side;
	int lineHeight; //needed
	int drawStart;
	int drawEnd;
	double dirX;
	double dirY;
	double deltaDistX;
	double deltaDistY;
	double stepX;
	double stepY;
	double sideDistX;
	double sideDistY;
	double posX;
	double posY;
	int texX;
	double rayDirX;
	double rayDirY;
} t_ray;

typedef struct s_line_params
{
	int x0;
	int y0;
	int x1;
	int y1;
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
} t_line_params;

typedef struct s_circle_params
{
	int cx;
	int cy;
	int radius;
	int color;
} t_circle_params;

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
void		*init_pos_dir_plane(t_player *player, char NSEW);
t_map		*init_map(void);
t_player	*init_player(double x, double y);
t_game *init_game(t_config *config);
t_ray	*init_ray(double x, double y);
void	*render(t_game *game);
void	*render_minimap(t_game *game);
void	init_events(t_game *game);
t_textures	*init_textures(t_config	*config);

// Validating map and parse
int	validate_line(const char *line);
void	process_map_line(t_config *config, const char *clean_line);
void	add_used_key(const char *key, char *used_keys[MAX_KEYS]);
int	key_already_used(const char *key, char *used_keys[MAX_KEYS]);
char	*trim_trailing_spaces(const char *line);
int is_empty_or_map_started(const char *line, int map_started);
void	parse_color_line(t_config *config, const char *line);
void	parse_texture_line(t_config *config, const char *line);
int	parse_color(const char *str, int *color);


//void validate_map(t_config *config);
void validate_map(t_map *map, t_config *config);
int	error(const char *message, int use_perror, t_game *g, t_config *c);
t_config *parse_cub_file(const char *file_path, t_config *config);

// Utils
void *ft_realloc(void *ptr, size_t old_size, size_t new_size);
char *ft_strncpy(char *dest, const char *src, size_t n);

// free
void		*free_config(t_config *config);
void		*free_player(t_player *player);
t_textures	*free_textures(t_textures *t, void *mlx);
void		*free_map(t_map *map);
void		*free_game(t_game *game);
int			cleanup_all(t_game	*game, t_config *config);
void		*free_ray(t_ray *ray);
void		free_used_keys(char **used_keys);

// textures
int load_textures(t_game *game, t_config *cfg);
void trim_whitespace(char *str);
t_image	*choose_texture(t_ray *ray, t_game *game);
int	get_txt_color(t_image *txt, int x, int y);

//render
void render_texture(t_game *game, t_ray *ray, int x);

//rays
t_ray	*cast_rays(t_game *game);
int	close_window(void *param);

//mini map
void normalize_direction(t_game *game);
void draw_circle(t_game *game, t_circle_params *params);
void draw_line(t_game *game, t_line_params *params, int color);
void update_line_coordinates(int *x0, int *y0, t_line_params *params);
void calculate_line_parameters(t_line_params *params);
int check_for_wall_collision(t_game *game, int x0, int y0);
void draw_square(t_game *game, int x, int y, int color);
int apply_shading(int i, int j, int color);

//utils
int	ft_isspace(char c);

#endif
