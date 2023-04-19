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

void	draw_minimap(t_window *window)
{
	int	x = -100;
	int	y = -100;
	
	while (y < 101)
	{
		x = -100;
		while (x < 100)
		{
			mlx_put_pixel(window->hud->hud_img, window->hud->minimap->pix_pos_x + x, window->hud->minimap->pix_pos_y + y, WHITE);
			x++;
		}
		y++;
	}
}