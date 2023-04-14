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

# define FOV 60
# define SPEED 10
# define DARKNESS_FACTOR 50

# define WHITE 0xffffffff
# define YELLOW 0xffff00ff
# define BLUE 0xffffff
# define PINK 0xff00ffff
# define RED 0xff0000ff
# define BLACK 0x0

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

typedef enum e_cube_type
{
	walkable,
	wall,
	empty,
	spawn
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
	t_cube_type		**cubes;
	int				width;
	int				height;
	mlx_texture_t	*textures[4];
	t_vector		*start_pos;
	t_vector		*start_dir;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
}					t_map;

typedef struct s_player
{
	t_vector	*pos;
	t_vector	*dir;
}			t_player;

typedef struct s_window
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	*player;
	t_map		*map;
}	t_window;

//free_utils.c
void		free_map(t_cube_type **cube);
void		free_window_struct(t_window *window);

//utils.c
int			on_screen(int x, int y);
t_cube_type	get_cube_type(t_vector *pos, t_map *map);

//rotate.c
void		rotate_hor_f(t_vector *before, t_vector *after, double angle);

// parser
t_map		*parse(int fd);
int			args_valid(int argc, char **argv);

// parser utils
void		set_map_value(t_map *map, int line, int column, char c);
void		print_file(t_list *line_list);

// vector utils
t_vector	*set_vec(t_vector *vec, double x, double y, double z);

//distance.c
double		distance(t_vector pos, t_vector target);
double		dot_product(t_vector v1, t_vector v2);
double		abs_vector(t_vector v);
double		distance_perpendicular(t_vector pos, t_vector dir, t_vector target);

//keyboard_input.c
void		escape_handler(void *arg);
void		player_movement(void *arg);

//raycasting.c
void		draw_scene(t_window *window);

//textures.c
double		ft_modf(double num);
u_int32_t	get_rgba_from_tex(mlx_texture_t *tex, int x, int y);
int			texture_x_value(mlx_texture_t *tex, t_vector *target, t_map *map,
				t_direction direction);
int			texture_y_value(mlx_texture_t *tex, int line_height, int window_y,
				int start);
int			dim_color(int color, double distance);

//colors.c
int			get_rgba(int r, int g, int b, int a);
int			get_red(int rgba);
int			get_green(int rgba);
int			get_blue(int rgba);
int			get_alpha(int rgba);

//utils/utils.c
int			min(int a, int b);
int			max(int a, int b);

#endif
