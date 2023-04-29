#include <cub3D.h>

static unsigned int	enemy_get_pix(double scale_x, double scale_y,
	mlx_texture_t *tex, t_enemy *enemy)
{
	unsigned int	color;
	const int		x = tex->width * fabs(scale_x);
	const int		y = tex->height * fabs(scale_y);
	int				pos;

	if (enemy->delta_angle > 0)
		pos = (y * tex->width + x) * 4;
	else
		pos = (y * tex->width + (tex->width - x)) * 4;
	color = get_rgba(tex->pixels[pos] * enemy->brightness,
			tex->pixels[pos + 1] * enemy->brightness,
			tex->pixels[pos + 2] * enemy->brightness,
			tex->pixels[pos + 3]);
	return (color);
}

static mlx_texture_t	*enemy_get_texture(t_enemy *enemy, int frame_count)
{
	//if (enemy->state == dead)
	return (enemy->walking_textures[frame_count]);
}

static int	enemy_adjust_frame_count(t_enemy *enemy)
{
	static int	cooldown = 0;
	static int	frame_count = 0;

	if (!(enemy->state == hunting || enemy->state == attacking))
		return (frame_count);
	if (cooldown < 1)
	{
		frame_count++;
		cooldown = 10;
	}
	cooldown--;
	if (frame_count >= enemy->walking_texture_nb)
		frame_count = 0;
	return (frame_count);
}

static	void	draw_single_enemy(t_window *window, t_enemy *enemy)
{
	const double		enemy_x_on_screen = WIDTH * (1 - sin(enemy->delta_angle)
			/ sin(FOV * M_PI / 360)) / 2;
	unsigned int		color;
	const t_vector		max = (t_vector){300 / enemy->dis, 500 / enemy->dis};
	t_vector_int		iter;
	const int			frame_count = enemy_adjust_frame_count(enemy);

	iter.y = -max.y;
	while (++iter.y < max.y)
	{
		iter.x = -max.x;
		while (++iter.x < max.x)
		{
			if (is_on_screen(enemy_x_on_screen + iter.x, HEIGHT / 2 + iter.y))
			{
				color = enemy_get_pix((max.x + iter.x) / max.x / 2,
						(iter.y + max.y) / 2 / max.y,
						enemy_get_texture(enemy, frame_count), enemy);
				if (get_alpha(color) != 0)
					mlx_put_pixel(window->img, enemy_x_on_screen
						+ iter.x, HEIGHT / 2 + iter.y, color);
			}
		}
	}
}

void	draw_enemies(t_window *window)
{
	int	i;

	i = 0;
	while (window->all_enemies[i])
	{
		if (fabs(window->all_enemies[i]->delta_angle * 180 / M_PI) < FOV / 2)
			if (window->all_enemies[i]->state == hunting
				|| window->all_enemies[i]->state == waiting
				|| window->all_enemies[i]->state == attacking)
				draw_single_enemy(window, window->all_enemies[i]);
		i++;
	}
}
