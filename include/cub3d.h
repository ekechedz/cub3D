/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:19:29 by ekechedz          #+#    #+#             */
/*   Updated: 2025/02/17 14:21:06 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <string.h>
//# include "../minilibx/mlx.h"
# include "/home/ekechedz/minilibx/mlx.h"
//# include "/home/nleite-s/Repositories/cub3d/minilibx/mlx.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "X11/Xlib.h"
# include "X11/keysym.h"
# include <sys/time.h>

// Constants
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define MOVE_SPEED 2
# define ROT_SPEED 5
# define FOV 66
# define MAX_DEPTH 20.0
# define M_PI 3.14159265358979323846
# define MINI_SIZE 250
# define TILE_SIZE 40
# define CUBE_SIZE 64
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

//move
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53
# define KEY_COUNT 65536

// Mini map
# define MINIMAP_SCALE 10
# define MINIMAP_X_OFFSET 20
# define MINIMAP_Y_OFFSET 20
# define PLAYER_COLOR 0xFF4500
# define WALL_COLOR 0x444444
# define FLOOR_COLOR 0x222222
# define EMPTY_COLOR 0x888888
# define RAY_COLOR 0x00FFAA
# define PLAYER_RADIUS 3
# define RAY_LENGTH 100

// Map Characters

# define MAX_KEYS 6

//Draw constants
# define CEILING 1
# define FLOOR 2

// Structs
typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector	*pos;
	t_vector	*dir;
	t_vector	*plane;
}	t_player;

typedef struct s_image
{
	void	*img_ptr;
	char	*buff;
	char	*fp;
	int		lstsize;
	int		bpp;
	int		endian;
	int		width;
	int		height;
	int		line_length;
}	t_image;

typedef struct s_textures
{
	t_image	*north;
	t_image	*east;
	t_image	*south;
	t_image	*west;
	t_image	*floor;
	t_image	*ceiling;
}	t_textures;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_config
{
	t_map		*map;
	t_textures	*textures;
	int			*floor_color;
	int			*ceiling_color;
	t_player	*player;
	char		*used_keys[MAX_KEYS];
	void		*mlx;
}	t_config;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_player		*player;
	t_map			*map;
	int				*floor_color;
	int				*ceiling_color;
	t_textures		*textures;
	int				*screen_data;
	void			*img;
	int				bpp;
	int				line_length;
	int				endian;
	struct timeval	last_time;
	int				key_st[KEY_COUNT];
	t_config		*config;
}	t_game;

typedef struct s_ray
{
	double		dist;
	t_vector	*hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		dir_x;
	double		dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		step_x;
	double		step_y;
	double		side_dist_x;
	double		side_dist_y;
	double		pos_x;
	double		pos_y;
	int			tex_x;
	double		ray_dir_x;
	double		ray_dir_y;
}	t_ray;

typedef struct s_line_params
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line_params;

typedef struct s_circle_params
{
	int	cx;
	int	cy;
	int	radius;
	int	color;
}	t_circle_params;

//Init functions
int			main_loop(t_game *game);
int			key_hook(int keycode, t_game *game);
int			key_release_hook(int keycode, t_game *game);
void		rotate_player(t_player *player, int direction, double delta_time);
void		move_player(t_game *game, int direction, double delta_time);
void		strafe_player(t_game *game, int direction, double delta_time);
t_config	*init_config(void);
t_image		*init_t_image(void);
t_vector	*init_vector(double x, double y);
void		*init_pos_dir_plane(t_player *player, char NSEW);
t_map		*init_map(void);
t_player	*init_player(double x, double y);
t_game		*init_game(t_config *config);
t_ray		*init_ray(double x, double y);
void		init_events(t_game *game);
t_textures	*init_textures(t_config	*config);

// Validating map and parse
int			validate_line(const char *line);
void		process_map_line(t_config *config, const char *clean_line);
void		add_used_key(const char *key, char *used_keys[MAX_KEYS]);
int			key_already_used(const char *key, char *used_keys[MAX_KEYS]);
int			all_keys_used(char *used_keys[MAX_KEYS]);
char		*trim_trailing_spaces(const char *line);
int			is_empty_or_map_started(const char *line, int map_started);
void		parse_color_line(t_config *config, char *line);
void		parse_texture_line(t_config *config, char *line);
int			parse_color(const char *str, int *color);
void		validate_map(t_map *map, t_config *config);
t_config	*parse_cub_file(const char *file_path, t_config *config);
void		handle_color_line(t_config *config, char *line, \
	char *key, int *color_field);
int			check_and_skip_comma(const char **str);
int			parse_single_color_component(const char **str);
int			parse_int(const char **str);

// Utils
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char		*ft_strncpy(char *dest, const char *src, size_t n);
int			ft_isspace(char c);
int			error(const char *message, int use_perror, t_game *g, t_config *c);
void		trim_whitespace(char *str);

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
int			load_textures(t_game *game, t_config *cfg);
t_image		*choose_texture(t_ray *ray, t_game *game);
int			get_txt_color(t_image *txt, int x, int y);

//render
void		render_texture(t_game *game, t_ray *ray, int x);
void		*render(t_game *game);
void		*render_minimap(t_game *game);

//rays
t_ray		*cast_rays(t_game *game);
int			close_window(void *param);

//mini map
void		normalize_direction(t_game *game);
void		draw_circle(t_game *game, t_circle_params *params);
void		draw_line(t_game *game, t_line_params *params, int color);
void		update_line_coordinates(int *x0, int *y0, t_line_params *params);
void		calculate_line_parameters(t_line_params *params);
int			check_for_wall_collision(t_game *game, int x0, int y0);
void		draw_square(t_game *game, int x, int y, int color);
int			apply_shading(int i, int j, int color);

#endif
