#include <cub3D.h>

static unsigned int	enemy_get_pix(double scale_x, double scale_y,
	mlx_texture_t *tex, t_enemy *enemy)
{
	int				pos;
	unsigned int	color;
	const int		x = tex->width * fabs(scale_x);
	const int		y = tex->height * fabs(scale_y);

	pos = (y * tex->width + x) * 4;
	color = get_rgba(tex->pixels[pos] * enemy->brightness,
			tex->pixels[pos + 1] * enemy->brightness,
			tex->pixels[pos + 2] * enemy->brightness,
			tex->pixels[pos + 3]);
	return (color);
}

static mlx_texture_t	*enemy_get_texture(t_enemy *enemy, int frame_count)
{
	if (enemy->state == attacking)
		return (enemy->attacking_tex[enemy->type][frame_count]);
	else if (enemy->state == dead)
		return (enemy->death_tex[enemy->type][enemy->death_frame_count % 4]);
	else
		return (enemy->walking_tex[enemy->type][frame_count]);
}

static int	enemy_adjust_frame_count(t_enemy *enemy, double delta_time)
{
	if (enemy->state == dead)
	{
		if (enemy->death_cooldown < 0 && enemy->death_frame_count < 3)
		{
			enemy->death_frame_count++;
			enemy->death_cooldown = 4 / (delta_time * 60);
		}
		enemy->death_cooldown--;
	}
	if (!(enemy->state == hunting || enemy->state == attacking))
		return (enemy->frame_count);
	if (enemy->frame_cooldown < 1)
	{
		enemy->frame_count++;
		enemy->frame_cooldown = ENEMY_FRAME_COOLDOWN / (delta_time * 60);
	}
	enemy->frame_cooldown--;
	if (enemy->frame_count >= enemy->tex_nb)
		enemy->frame_count = 0;
	return (enemy->frame_count);
}

static	void	draw_single_enemy(t_window *window, t_enemy *enemy)
{
	unsigned int	color;
	t_vector_int	iter;
	const t_vector	lim = (t_vector){ENEMY_WIDTH / enemy->dis,
		ENEMY_HEIGHT / enemy->dis};
	const int		frame_count = enemy_adjust_frame_count(enemy, window->mlx->delta_time);

	iter.y = max(-lim.y, -HEIGHT / 2 - ENEMY_Y_OFFSET / enemy->dis);
	while (++iter.y < lim.y
		&& iter.y < HEIGHT / 2 - ENEMY_Y_OFFSET / enemy->dis)
	{
		iter.x = max(-lim.x, -500);
		while (++iter.x < lim.x && iter.x < 500)
		{
			if (!is_on_screen(enemy->x_on_screen + iter.x,
					HEIGHT / 2 + iter.y + ENEMY_Y_OFFSET / enemy->dis))
				continue ;
			color = enemy_get_pix((lim.x + iter.x) / lim.x / 2,
					(iter.y + lim.y) / 2 / lim.y,
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
			if (window->all_enemies[i]->state == hunting
				|| window->all_enemies[i]->state == attacking
				|| window->all_enemies[i]->state == waiting
				|| window->all_enemies[i]->state == dead)
				draw_single_enemy(window, window->all_enemies[i]);
		i++;
	}
}
