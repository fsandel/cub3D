#include <cub3D.h>

void	put_square(mlx_image_t *img, t_vector_f *pos, int color)
{
	int			i;
	int			j;

	i = -3;
	while (i < 4)
	{
		j = -3;
		while (j < 4)
		{
			if (pos->x + j > 0 && pos->x + j < WIDTH
				&& pos->y + i > 0 && pos->y + i < HEIGHT)
				mlx_put_pixel(img, pos->x + j, pos->y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_window *window)
{
	int	x;
	int	y;
	int	width;
	int	height;

	width = WIDTH / window->map->width;
	height = HEIGHT / window->map->height;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y / height < window->map->height
				&& x / width < window->map->width
				&& window->map->cubes[y / height][x / width] == wall)
				mlx_put_pixel(window->img, x, y, 0xff0000ff);
			y++;
		}
		x++;
	}
}
