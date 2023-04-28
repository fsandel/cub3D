#include <cub3D.h>

static unsigned int	enemy_get_pix(double scale_x, double scale_y,
	mlx_texture_t *tex)
{
	unsigned int	color;
	const int		x = tex->width * fabs(scale_x);
	const int		y = tex->height * fabs(scale_y);
	const int		pos = (y * tex->width + x) * 4;

	color = get_rgba(tex->pixels[pos], tex->pixels[pos + 1],
			tex->pixels[pos + 2], tex->pixels[pos + 3]);
	return (color);
}

static	void	draw_single_enemy(t_window *window, t_enemy *enemy)
{
	const double		delta_angle = atan2(fabs(enemy->dir.x), fabs(enemy->dir.y)) - atan2((window->player->dir->x), (window->player->dir->y));
	const double		enemy_x_on_screen = WIDTH * (1 - sin(delta_angle) / sin(FOV * M_PI / 360)) / 2;
	unsigned int		color;
	const t_vector		max = (t_vector){600 / enemy->dis, 1000 / enemy->dis};
	t_vector_int		iter;

	iter.y = 0;
	while (iter.y < max.y)
	{
		iter.x = 0;
		while (iter.x < max.x)
		{
			if (is_on_screen(enemy_x_on_screen + iter.x - max.x / 2, HEIGHT / 2 + iter.y - max.y / 2))
			{
				color = enemy_get_pix(iter.x / max.x, iter.y / max.y, enemy->textures[0]);
				if (color <= 4000000000)
					mlx_put_pixel(window->img, enemy_x_on_screen + iter.x - max.x / 2, HEIGHT / 2 + iter.y - max.y / 2, color);
			}
			iter.x++;
		}
		iter.y++;
	}
}

void	draw_enemies(t_window *window)
{
	int	i;

	i = 0;
	while (window->all_enemies[i])
	{
		if (window->all_enemies[i]->state == hunting || window->all_enemies[i]->state == waiting)
			draw_single_enemy(window, window->all_enemies[i]);
		i++;
	}
}
