#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

// parser
int	parse(int fd);
int	args_valid(int argc, char **argv);

#endif
