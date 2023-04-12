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

typedef struct s_vector_f
{
	double	x;
	double	y;
	double	z;
}			t_vector_f;

typedef enum e_cube_type
{
	walkable,
	wall,
	empty,
	spawn
}	t_cube_type;

typedef struct s_map
{
	t_cube_type	**cubes;
	int			width;
	int			height;
	t_vector_f	*start_pos;
	t_vector_f	*start_dir;
}	t_map;

typedef struct s_player
{
	t_vector_f	*pos;
	t_vector_f	*dir;
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
t_cube_type	get_cube_type(t_vector_f *pos, t_map *map);

//2dtest.c
void		put_square(mlx_image_t *img, t_vector_f *pos, int color);
void		draw_map(t_window *window);

//rotate.c
void		rotate_hor_f(t_vector_f *before, t_vector_f *after, double angle);

//movement.c
void		player_movement(void *arg);
void		put_player(t_window *window, int color);

// parser
t_map		*parse(int fd);
int			args_valid(int argc, char **argv);

// parser utils
void		set_map_value(t_map *map, int line, int column, char c);
void		print_file(t_list *line_list);

// vector utils
t_vector_f	*set_vec(t_vector_f *vec, double x, double y, double z);

#endif
