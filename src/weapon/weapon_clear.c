#include <cub3D.h>

void	clean_weapon(t_window *window)
{
	const int	size = min(WIDTH, HEIGHT) / 2.5;
	const int	offset_x = WIDTH / 2;
	const int	offset_y = HEIGHT - size;
	int			x_iter;
	int			y_iter;

	y_iter = -size;
	while (++y_iter < size)
	{
		if (y_iter + offset_y >= HEIGHT)
			continue ;
		x_iter = -size;
		while (++x_iter < size)
		{
			if (x_iter + offset_x >= WIDTH)
				continue ;
			mlx_put_pixel(window->hud->hud_img,
				x_iter + offset_x, y_iter + offset_y, 0x00000000);
		}
	}
}

void	clean_cross_hair(t_window *window)
{
	int			x_iter;
	int			y_iter;
	const int	size = 35 + WEAPON_COOLDOWN;
	const int	width = 0;

	y_iter = -size - 1;
	while (y_iter++ <= size)
	{
		x_iter = -width - 1;
		while (x_iter++ <= width)
			mlx_put_pixel(window->hud->hud_img,
				x_iter + WIDTH / 2, y_iter + HEIGHT / 2, 0x00000000);
	}
	y_iter = -width - 1;
	while (y_iter++ <= width)
	{
		x_iter = -size - 1;
		while (x_iter++ <= size)
			mlx_put_pixel(window->hud->hud_img,
				x_iter + WIDTH / 2, y_iter + HEIGHT / 2, 0x00000000);
	}
}
