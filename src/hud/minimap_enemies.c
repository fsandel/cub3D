#include <cub3D.h>
#include "minimap_colors.h"

static void	put_square(mlx_image_t *img, int x, int y, int color)
{
	int			i;
	int			j;
	const int	size = 3;

	j = -size;
	while (j <= size)
	{
		i = -size;
		while (i <= size)
		{
			mlx_put_pixel(img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

static void	draw_minimap_single_enemy(t_enemy *enemy, t_window *window)
{
	const double	scale = window->hud->minimap->radius
		/ window->hud->minimap->zoom;
	const int		x_pos = (enemy->pos.x - window->player->pos->x) * scale
		+ window->hud->minimap->pix_pos_x;
	const int		y_pos = (enemy->pos.y - window->player->pos->y) * scale
		+ window->hud->minimap->pix_pos_y;

	if (on_screen(x_pos, y_pos)
		&& quad_add(x_pos - window->hud->minimap->pix_pos_x,
			y_pos - window->hud->minimap->pix_pos_y)
		< window->hud->minimap->radius - 1)
		put_square(window->hud->hud_img, x_pos, y_pos, ENEMY);
}

void	draw_minimap_enemies(t_window *window)
{
	int	i;

	i = 0;
	while (window->all_enemies[i])
	{
		if (window->all_enemies[i]->dis < 5)
			if (window->all_enemies[i]->state != dead
				&& window->all_enemies[i]->state != out_of_range)
				draw_minimap_single_enemy(window->all_enemies[i], window);
		i++;
	}
}
