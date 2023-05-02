#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h> //open
# include <unistd.h> //close, read, write
# include <stdio.h> //printf, perror, strerror
# include <stdlib.h> //malloc, free, exit
# include <math.h>

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"

# define WIDTH 1000
# define HEIGHT 1000

# define FOV 45
# define SPEED 0.05f
# define TURN_SPEED 0.05f
# define DARKNESS_FACTOR 50

# define WHITE 0xffffffff
# define YELLOW 0xffff00ff
# define BLUE 0xffffff
# define PINK 0xff00ffff
# define RED 0xff0000ff
# define BLACK 0x000000ff
# define ORANGE 0xffa500ff

enum e_parser_error
{
	no_error,
	opt_unknown,
	no_map,
	no_opts,
	map_not_last,
	multiple_maps,
	invalid_texture,
	invalid_color,
	too_many_textures,
	too_many_spawns,
	too_many_colors,
	missing_option,
	invalid_map
};

typedef struct s_parser_state
{
	bool				map_parsed;
	bool				f_parsed;
	bool				c_parsed;
	bool				contains_door;
	enum e_parser_error	error_type;
}			t_parser_state;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

typedef struct s_file_content
{
	t_list	*map_lines;
	t_list	*option_lines;
}			t_file_content;

typedef enum e_cube_type
{
	walkable,
	wall,
	empty,
	spawn,
	door_open,
	door_closed
}	t_cube_type;

typedef enum e_direction
{
	north,
	east,
	south,
	west,
}	t_direction;

typedef struct s_map
{
	t_parser_state	*state;
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
	mlx_texture_t	*placeholder;
}					t_map;

typedef struct s_player
{
	t_vector	*pos;
	t_vector	*dir;
}			t_player;

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
	mlx_image_t	*hud_img;
	t_fps		*fps;
	t_minimap	*minimap;
}	t_hud;

typedef struct s_window
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	*player;
	t_map		*map;
	t_hud		*hud;
}	t_window;

//free_utils.c
void			free_window_struct(t_window *window);
void			free_filecontent(t_file_content *file_content);
void			free_cubes(t_map *map);

//utils.c
int				on_screen(int x, int y);
t_cube_type		get_cube_type(t_vector *pos, t_map *map);
bool			ft_iswhitespace(char *str);

//rotate.c
void			rotate_hor_f(t_vector *before, t_vector *after, double angle);
void			norm(t_vector *v, double future_length);

//math/misc.c
double			quad_add(double x, double y);
double			ft_modf(double num);

// validate_map.c
bool			map_is_valid(t_map *map);
// validate_options.c
bool			options_are_valid(t_map *map);

// parser
t_map			*parse(int fd);
int				args_valid(int argc, char **argv);

//handle error
void			parser_error(t_file_content *file_content, t_map *map);

// parse_options.c
void			parse_options(t_list *option_lines, t_map *map);
void			parse_map(char *str, int fd, t_map *map,
					t_file_content *file_content);

// check_syntax.c
bool			is_valid_map_str(char *map_str);
bool			is_valid_tex_str(char *tex_str);
bool			is_valid_f_c_str(char *f_c_str);

// map utils
void			set_floor_color(t_map *map, int color);
void			set_ceiling_color(t_map *map, int color);
void			set_cube_value(t_map *map, int line, int column, char c);

// vector utils
t_vector		*set_vec(t_vector *vec, double x, double y, double z);

//distance.c
double			distance(t_vector pos, t_vector target);
double			dot_product(t_vector v1, t_vector v2);
double			abs_vector(t_vector v);
double			distance_perpendicular(t_vector pos, t_vector dir,
					t_vector target);

//keyboard_input.c
void			escape_handler(void *arg);
void			player_movement(void *arg);

//raycasting.c
void			draw_scene(t_window *window);

//textures.c
u_int32_t		get_rgba_from_tex(const mlx_texture_t *tex, int x, int y);
int				texture_x_value(const mlx_texture_t *tex, t_vector *target,
					t_direction direction);
int				texture_y_value(const mlx_texture_t *tex, int line_height,
					int window_y, int start);
int				dim_color(int color, double distance);
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

//hud.c
void			setup_hud(t_window *window);
void			draw_hud(void *arg);

//minimap.c
void			draw_minimap(t_window *window);
void			draw_minimap_background(t_window *window);

//doors.c
void			door_handler(mlx_key_data_t keydata, void *arg);

#endif
