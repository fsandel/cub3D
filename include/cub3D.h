/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsandel <fsandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:39:31 by fsandel           #+#    #+#             */
/*   Updated: 2023/04/11 09:28:50 by fsandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h> //open
# include <unistd.h> //close, read, write
# include <stdio.h> //printf, perror, strerror
# include <stdlib.h> //malloc, free, exit
# include <math.h>

//# include <MLX42.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
//# include <libft.h>
# include "../lib/libft/libft.h"

# define WIDTH 1000
# define HEIGHT 1000

typedef struct s_vector_f
{
	double	x;
	double	y;
	double	z;
}			t_vector_f;

typedef struct s_v_i
{
	int	x;
	int	y;
	int	z;
}		t_v_i;

typedef struct s_player
{
	t_v_i	*pos;
	t_vector_f	*dir;
}			t_player;

typedef struct s_window
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	*player;
	char		**map;
}			t_window;

#endif
