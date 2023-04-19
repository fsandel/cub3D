#include <cub3D.h>
bool is_on_screen(int offset_x, int offset_y, t_player *player, t_map *map)
{
	const int pos_x = player->pos->x * WIDTH / map->width + offset_x;
	const int pos_y = player->pos->y * HEIGHT / map->height + offset_y;

	if (pos_x > 0 && pos_x < WIDTH && pos_y > 0 && pos_y < HEIGHT)
		return (true);
	else
		return (false);
}

static bool is_on_map(double x, double y, t_map *map)
{
	if (x >= 0 && y >= 0 && x < map->width && y < map->height)
		return (true);
	else
		return (false);
}

void	draw_minimap(t_window *window)
{
	const int	size = 100;
	int	x_iter;
	int	y_iter;
	const double	zoom = 3;
	double	x_pos;
	double	y_pos;
	t_vector pos;

	pos.z = 0;
	y_iter = - size;
	while (y_iter <= size)
	{
		x_iter = -size;
		while (x_iter <= size)
		{
			if (sqrt(x_iter * x_iter + y_iter * y_iter) < 100)
			{
				x_pos = window->player->pos->x + x_iter * zoom / size;
				y_pos = window->player->pos->y + y_iter * zoom / size;
				set_vec(&pos, x_pos, y_pos, 0);
				if (is_on_map(x_pos, y_pos, window->map))
				{
					if (get_cube_type(&pos, window->map) == wall)
						mlx_put_pixel(window->hud->hud_img, window->hud->minimap->pix_pos_x + x_iter, window->hud->minimap->pix_pos_y + y_iter, WHITE);
					else
						mlx_put_pixel(window->hud->hud_img, window->hud->minimap->pix_pos_x + x_iter, window->hud->minimap->pix_pos_y + y_iter, BLUE);
				}
				else
					mlx_put_pixel(window->hud->hud_img, window->hud->minimap->pix_pos_x + x_iter, window->hud->minimap->pix_pos_y + y_iter, RED);
				if (abs(x_iter) < 3 && abs(y_iter) < 3)
					mlx_put_pixel(window->hud->hud_img, window->hud->minimap->pix_pos_x + x_iter, window->hud->minimap->pix_pos_y + y_iter, PINK);
			}
			x_iter++;
		}
		y_iter++;
	}
}