#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h> //open
# include <unistd.h> //close, read, write
# include <stdio.h> //printf, perror, strerror
# include <stdlib.h> //malloc, free, exit
# include <math.h>

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"

# include "design.h"

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_vector_int
{
	int	x;
	int	y;
}	t_vector_int;

typedef struct s_file_content
{
	t_list	*map_lines;
	t_list	*option_lines;
}	t_file_content;

typedef enum e_cube_type
{
	empty,
	spawn,
	door_open,
	walkable,
	wall,
	door_closed,
	health_full,
	health_empty,
	ammo_full,
	ammo_empty,
	exit_cube
}	t_cube_type;

typedef enum e_direction
{
	north,
	east,
	south,
	west,
}	t_direction;

typedef enum e_enemy_state
{
	dead,
	out_of_range,
	waiting,
	hunting,
	attacking
}	t_enemy_state;

typedef struct s_enemy
{
	t_vector		pos;
	t_vector		dir;
	t_enemy_state	state;
	int				hitpoints;
	mlx_texture_t	*walking_textures[9];
	mlx_texture_t	*attacking_textures[9];
	mlx_texture_t	*dead_textures[1];
	int				walking_texture_nb;
	double			dis;
	int				frame_count;
	int				frame_cooldown;
	double			delta_angle;
	int				x_on_screen;
	double			brightness;
}	t_enemy;

typedef struct s_map
{
	t_cube_type		**cubes;
	int				width;
	int				height;
	mlx_texture_t	*textures[4];
	t_vector		*start_pos;
	t_vector		*start_dir;
	int				floor_color;
	int				ceiling_color;
	bool			has_spawn;
	mlx_texture_t	*door;
	mlx_texture_t	*health_text[2];
	mlx_texture_t	*ammo_text[2];
	mlx_texture_t	*exit_text[2];
	t_list			*enemy_list;
}	t_map;

typedef struct s_player
{
	t_vector	*pos;
	t_vector	*dir;
	int			hp;
	int			ammo;
}	t_player;

typedef struct s_fps
{
	int			fps_num;
	int			*frame_time;
	mlx_image_t	*fps_image;
}	t_fps;

typedef struct s_minimap
{
	int	pix_pos_x;
	int	pix_pos_y;
	int	radius;
	int	zoom;
}	t_minimap;

typedef struct s_hud
{
	mlx_image_t		*hud_img;
	t_fps			*fps;
	t_minimap		*minimap;
}	t_hud;

typedef struct s_window
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	*player;
	t_map		*map;
	t_hud		*hud;
	t_enemy		**all_enemies;
	int			fog;
	bool		redraw;
	bool		active;
}	t_window;

//free_utils.c
void			free_window_struct(t_window *window);

//utils.c
t_cube_type		get_cube_type(t_vector *pos, t_map *map);

//rotate.c
void			rotate(t_vector *before, t_vector *after, double angle);
void			norm(t_vector *v, double future_length);

//math/misc.c
double			quad_add(double x, double y);
double			ft_modf(double num);
int				sign(double x);

// validate_map.c
bool			map_is_valid(t_map *map);

// validate_options.c
bool			options_are_valid(t_map *map);

// parser
t_map			*parse(int fd);
int				args_valid(int argc, char **argv);

// parse_options.c
void			parse_options(t_list *option_lines, t_map *map);

// check_syntax.c
bool			is_valid_map_str(char *map_str);
bool			is_valid_tex_str(char *tex_str);
bool			is_valid_f_c_str(char *f_c_str);

// map utils
void			set_floor_color(t_map *map, int color);
void			set_ceiling_color(t_map *map, int color);
void			set_cube_value(t_map *map, int line, int column, char c);

// vector utils
t_vector		*set_vec(t_vector *vec, double x, double y);

//distance.c
double			distance(t_vector pos, t_vector target);
double			distance_perpendicular(t_vector pos, t_vector dir,
					t_vector target);

//keyboard_input.c
void			player_movement(void *arg);
void			cub_key_hook(mlx_key_data_t keydata, void *arg);
void			mouse_movement(void *arg);

//raycasting.c
void			draw_scene(t_window *window);

//textures.c
int				get_rgba_from_tex(const mlx_texture_t *tex, int x, int y);
int				texture_x_value(const mlx_texture_t *tex, t_vector *target,
					t_direction direction);
int				texture_y_value(const mlx_texture_t *tex, int line_height,
					int window_y, int start);
mlx_texture_t	*get_texture(t_window *window, t_vector *target,
					t_direction direction);

//colors.c
int				get_rgba(int r, int g, int b, int a);
int				get_red(int rgba);
int				get_green(int rgba);
int				get_blue(int rgba);
int				get_alpha(int rgba);

//utils/utils.c
double			min(double a, double b);
double			max(double a, double b);
bool			is_on_map(double x, double y, t_map *map);
bool			is_on_screen(int x, int y);

//hud.c
void			setup_hud(t_window *window);
void			draw_hud(void *arg);

//minimap.c
void			draw_minimap(t_window *window);
void			draw_minimap_background(t_window *window);
void			draw_minimap_enemies(t_window *window);

//doors.c
void			door_handler(t_window *window, mlx_key_data_t keydata);

//movement.c
bool			change_player_position(t_window *window, double angle);
bool			rotate_camera(t_window *window, double turn_speed);

//enemies
void			enemie_handler(void *arg);
void			draw_enemies(t_window *window);
void			check_enemies_state(t_window *window);
void			move_enemies(t_window *window);
void			set_enemy_dir(t_enemy *enemy, t_player *player);
void			setup_enemy_struct(t_window *window, t_map *map);
void			attack_enemies(t_window *window);

//player_attack.c
void			player_attack(void *arg);

//endcondition.c
void			check_dead(void *arg);

//start_end_screen.c
void			draw_tex_to_screen(mlx_image_t *img, char *texture_string);
void			start_screen_hook(mlx_key_data_t keydata, void *arg);

//setup.c
t_window		*general_setup(t_map *map);

//main.c
void			redraw_window(void *arg);

#endif
