#include <cub3D.h>

static unsigned int	enemy_get_pix(double scale_x, double scale_y,
	mlx_texture_t *tex, t_enemy *enemy)
{
	int				pos;
	unsigned int	color;
	const int		x = tex->width * fabs(scale_x);
	const int		y = tex->height * fabs(scale_y);

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
	if (enemy->state == dead)
		return (enemy->dead_textures[0]);
	else if (enemy->state == attacking)
		return (enemy->attacking_textures[frame_count]);
	else
		return (enemy->walking_textures[frame_count]);
}

static int	enemy_adjust_frame_count(t_enemy *enemy)
{
	if (!(enemy->state == hunting || enemy->state == attacking))
		return (enemy->frame_count);
	if (enemy->frame_cooldown < 1)
	{
		enemy->frame_count++;
		enemy->frame_cooldown = ENEMY_FRAME_COOLDOWN;
	}
	enemy->frame_cooldown--;
	if (enemy->frame_count >= enemy->walking_texture_nb)
		enemy->frame_count = 0;
	return (enemy->frame_count);
}

static	void	draw_single_enemy(t_window *window, t_enemy *enemy)
{
	unsigned int	color;
	t_vector_int	iter;
	const t_vector	max = (t_vector){ENEMY_WIDTH / enemy->dis,
		ENEMY_HEIGHT / enemy->dis};
	const int		frame_count = enemy_adjust_frame_count(enemy);

	iter.y = -max.y;
	while (++iter.y < max.y)
	{
		iter.x = -max.x;
		while (++iter.x < max.x)
		{
			if (!is_on_screen(enemy->x_on_screen + iter.x,
					HEIGHT / 2 + iter.y + ENEMY_Y_OFFSET / enemy->dis))
				continue ;
			color = enemy_get_pix((max.x + iter.x) / max.x / 2,
					(iter.y + max.y) / 2 / max.y,
					enemy_get_texture(enemy, frame_count), enemy);
			if (get_alpha(color) != 0)
				mlx_put_pixel(window->img, enemy->x_on_screen + iter.x,
					HEIGHT / 2 + iter.y + ENEMY_Y_OFFSET / enemy->dis, color);
		}
	}
}

void	draw_enemies(t_window *window)
{
	int	i;

	i = 0;
	while (window->all_enemies[i])
	{
		if (fabs(window->all_enemies[i]->delta_angle * 180 / M_PI) < FOV / 0.75)
			if (window->all_enemies[i]->state != out_of_range)
				draw_single_enemy(window, window->all_enemies[i]);
		i++;
	}
}
