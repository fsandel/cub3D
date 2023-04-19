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
	const int		size = window->hud->minimap->radius;
	const double	zoom = window->hud->minimap->zoom;
	int				x_iter;
	int				y_iter;
	t_vector		pos;

	pos.z = 0;
	y_iter = - size;
	while (y_iter <= size)
	{
		x_iter = -size;
		while (x_iter <= size)
		{
			if (sqrt(x_iter * x_iter + y_iter * y_iter) < size - 2)
			{
				pos.x = window->player->pos->x + x_iter * zoom / size;
				pos.y = window->player->pos->y + y_iter * zoom / size;
				if (is_on_map(pos.x, pos.y, window->map))
				{
					if (get_cube_type(&pos, window->map) == wall)
						mlx_put_pixel(window->hud->hud_img, window->hud->minimap->pix_pos_x + x_iter, window->hud->minimap->pix_pos_y + y_iter, WHITE);
					else
						mlx_put_pixel(window->hud->hud_img, window->hud->minimap->pix_pos_x + x_iter, window->hud->minimap->pix_pos_y + y_iter, window->map->floor_color);
				}
				else
					mlx_put_pixel(window->hud->hud_img, window->hud->minimap->pix_pos_x + x_iter, window->hud->minimap->pix_pos_y + y_iter, window->map->ceiling_color);
				if (abs(x_iter) < 3 && abs(y_iter) < 3)
					mlx_put_pixel(window->hud->hud_img, window->hud->minimap->pix_pos_x + x_iter, window->hud->minimap->pix_pos_y + y_iter, PINK);
			}
			else if (sqrt(x_iter * x_iter + y_iter * y_iter) < size)
				mlx_put_pixel(window->hud->hud_img, window->hud->minimap->pix_pos_x + x_iter, window->hud->minimap->pix_pos_y + y_iter, BLACK);
			x_iter++;
		}
		y_iter++;
	}
}