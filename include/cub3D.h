#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef enum e_square_type
{
	empty,
	floor,
	wall
}	t_square_type;

typedef struct s_map
{
	int				height;
	int				width;
	t_square_type	**square;
}	t_map;

// parser
int		parse(int fd);
int		args_valid(int argc, char **argv);
// parser utils
void	set_map_value(t_map *map, int line, int column, char c);
void	print_file(t_list *line_list);

#endif
