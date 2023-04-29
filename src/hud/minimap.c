#include <cub3D.h>
#include "minimap_colors.h"

void	draw_minimap_fov(t_window *window);
void	draw_minimap_border(t_window *window);

void	put_pixel_minimap(int x_iter, int y_iter, t_window *window, int color)
{
	if (window->hud->minimap->pix_pos_x + x_iter < 0)
		return ;
	if (window->hud->minimap->pix_pos_y + y_iter > WIDTH)
		return ;
	if (window->hud->minimap->pix_pos_x + x_iter < 0)
		return ;
	if (window->hud->minimap->pix_pos_x + y_iter > HEIGHT)
		return ;
	mlx_put_pixel(
		window->hud->hud_img,
		window->hud->minimap->pix_pos_x + x_iter,
		window->hud->minimap->pix_pos_y + y_iter,
		color
		);
}

static void	minimap_choose_surrounding(t_window *window, int x_iter, int y_iter)
{
	t_vector	pos;

	pos.x = window->player->pos->x + (double)(x_iter
			* window->hud->minimap->zoom) / window->hud->minimap->radius;
	pos.y = window->player->pos->y + (double)(y_iter
			* window->hud->minimap->zoom) / window->hud->minimap->radius;
	if (!is_on_map(pos.x, pos.y, window->map))
		put_pixel_minimap(x_iter, y_iter, window, OUTSIDE);
	else if (get_cube_type(&pos, window->map) == wall)
		put_pixel_minimap(x_iter, y_iter, window, WALL);
	else if (get_cube_type(&pos, window->map) == door_closed)
		put_pixel_minimap(x_iter, y_iter, window, DOOR);
}

static void	draw_minimap_surrounding(t_window *window)
{
	int				x_iter;
	int				y_iter;
	const int		size = window->hud->minimap->radius;

	y_iter = -size;
	while (y_iter <= size)
	{
		x_iter = -size;
		while (x_iter <= size)
		{
			if (quad_add(x_iter, y_iter) <= size)
				minimap_choose_surrounding(window, x_iter, y_iter);
			x_iter++;
		}
		y_iter++;
	}
}

static void	draw_minimap_player(t_window *window)
{
	int			x_iter;
	int			y_iter;
	const int	player_size = 4;

	y_iter = -player_size;
	while (y_iter <= player_size)
	{
		x_iter = -player_size;
		while (x_iter <= player_size)
		{
			if (quad_add(x_iter, y_iter) < player_size)
				put_pixel_minimap(x_iter, y_iter, window, PLAYER);
			x_iter++;
		}
		y_iter++;
	}
}

void	draw_minimap(t_window *window)
{
	draw_minimap_background(window);
	draw_minimap_fov(window);
	draw_minimap_surrounding(window);
	draw_minimap_player(window);
	draw_minimap_border(window);
	draw_minimap_enemies(window);
}
