#include <cub3D.h>

static unsigned int	enemy_get_pix(double scale_x, double scale_y, mlx_texture_t *tex)
{
	unsigned int	color;
	const int	x = tex->width * fabs(scale_x);
	const int	y = tex->height * fabs(scale_y);
	const int	pos = (y * tex->width + x) * 4;

	//printf("%f   %f\n", scale_x,scale_y);
	color = get_rgba(tex->pixels[pos], tex->pixels[pos + 1],
			tex->pixels[pos + 2], tex->pixels[pos + 3]);
	return (color);

}
static	void	draw_single_enemy(t_window *window, t_enemy *enemy)
{
	if (enemy->state != hunting)
		return ;
	const double	enemy_angle = atan2(fabs(enemy->dir.x), fabs(enemy->dir.y));
	const double	player_angle  = atan2((window->player->dir->x), (window->player->dir->y));
	const double	delta_angle = (enemy_angle - player_angle);
	const double	enemy_x_on_screen = WIDTH / 2 - WIDTH * sin(delta_angle) / sin(FOV * M_PI / 360) / 2;
	const double	line_height = HEIGHT / enemy->dis;
	const double	scale = line_height / HEIGHT;
	unsigned int	color;

	double	x_max = 600 * scale;
	double	y_max = 1000 * scale;
	int	x_iter;
	int	y_iter = 0;
	while (y_iter < y_max)
	{
		x_iter = 0;
		while (x_iter < x_max)
		{
			if (enemy_x_on_screen + x_iter - x_max / 2> 0 && enemy_x_on_screen + x_iter - x_max / 2< WIDTH)
				if ( HEIGHT/2 + y_iter - y_max / 2> 0 &&  HEIGHT/2 + y_iter - y_max / 2< HEIGHT)
				{
					color = enemy_get_pix(x_iter/x_max, y_iter / y_max, enemy->textures[0]);
					//color = 0x000000ff;
					if (color <= 4000000000)
						mlx_put_pixel(window->img, enemy_x_on_screen + x_iter - x_max / 2, HEIGHT/2 + y_iter - y_max / 2, color);
				}
			x_iter++;
		}
		y_iter++;
	}
}

void	draw_enemies(t_window *window)
{
	int	i;

	i = 0;
	while (window->all_enemies[i])
		draw_single_enemy(window, window->all_enemies[i++]);
}
