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

typedef struct s_map
{
	char	**array;
	int		width;
	int		heigth;
}			t_map;

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
}			t_window;

//utils.c
int		on_screen(int x, int y);
char	get_map_char(t_vector_f *pos, t_map *map);

//2dtest.c
void	put_square(mlx_image_t *img, t_vector_f *pos, int color);
void	draw_map(t_window *window);

#endif
