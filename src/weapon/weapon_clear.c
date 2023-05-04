#include <cub3D.h>

void	clean_weapon(t_window *window)
{
	int				x_iter;
	int				y_iter;

	y_iter = -WEAPON_SIZE_Y;
	while (++y_iter < WEAPON_SIZE_Y)
	{
		if (y_iter + WEAPON_OFFSET_Y >= HEIGHT)
			continue ;
		x_iter = -WEAPON_SIZE_X;
		while (++x_iter < WEAPON_SIZE_X)
		{
			if (x_iter + WEAPON_OFFSET_X >= WIDTH)
				continue ;
			mlx_put_pixel(window->hud->hud_img,
				x_iter + WEAPON_OFFSET_X, y_iter + WEAPON_OFFSET_Y, 0x00000000);
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
