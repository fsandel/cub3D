#include <cub3D.h>
#include "minimap_colors.h"

void	put_pixel_minimap(int x_iter, int y_iter, t_window *window, int color);

static void	draw_minimap_ray(t_window *window, t_vector dir, t_hud *hud)
{
	t_vector	pos;
	double		x;
	double		y;
	const char	size = hud->minimap_radius;
	const char	zoom = hud->minimap_zoom;

	set_vec(&pos, window->player->pos.x, window->player->pos.y);
	while (get_cube_type(&pos, window->map) < wall)
	{
		x = (pos.x - window->player->pos.x) * size / zoom + hud->minimap_pos_x;
		y = (pos.y - window->player->pos.y) * size / zoom + hud->minimap_pos_y;
		if (quad_add(x - hud->minimap_pos_x, y - hud->minimap_pos_y) <= size)
			mlx_put_pixel(window->hud->hud_img, x, y, CONE);
		pos.x -= dir.x * 0.015;
		pos.y -= dir.y * 0.015;
	}
}

void	draw_minimap_fov(t_window *window)
{
	t_vector		dir;
	int				iter;
	const double	delta_angle = M_PI / 360;

	iter = -FOV;
	while (iter <= FOV)
	{
		dir.x = window->player->dir.x;
		dir.y = window->player->dir.y;
		rotate(&dir, &dir, iter * delta_angle);
		draw_minimap_ray(window, dir, window->hud);
		iter++;
	}
}

void	draw_minimap_border(t_window *window)
{
	int			x_iter;
	int			y_iter;
	double		distance;
	const char	border = 3;
	const char	radius = window->hud->minimap_radius;

	y_iter = -radius - border;
	while (y_iter <= radius + border)
	{
		x_iter = -radius - border;
		while (x_iter <= radius + border)
		{
			distance = quad_add(x_iter, y_iter);
			if (distance >= radius && distance <= radius + border)
				put_pixel_minimap(x_iter, y_iter, window, BORDER);
			x_iter++;
		}
		y_iter++;
	}
}

void	draw_minimap_background(t_window *window)
{
	int			x_iter;
	int			y_iter;
	const char	border = 3;
	const char	radius = window->hud->minimap_radius;

	y_iter = -radius - border;
	while (y_iter <= radius + border)
	{
		x_iter = -radius - border;
		while (x_iter <= radius + border)
		{
			if (quad_add(x_iter, y_iter) <= radius)
				put_pixel_minimap(x_iter, y_iter, window, FLOOR);
			x_iter++;
		}
		y_iter++;
	}
}
