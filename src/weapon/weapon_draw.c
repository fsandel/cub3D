#include <cub3D.h>

static int	weapon_get_color(double scale_x, double scale_y,
				mlx_texture_t *tex);
void		clean_cross_hair(t_window *window);
static int	calc_weap_tex(t_window *window);

void	draw_weapon_loop_hook(void *arg)
{
	t_window	*window;

	window = (t_window *)arg;
	if (window->state != game_screen)
		return ;
	if (mlx_is_key_down(window->mlx, MLX_KEY_1))
		swap_weapon(window);
	if (mlx_is_key_down(window->mlx, MLX_KEY_2))
		window->player->weapon->weapon_type = torch;
	if (mlx_is_key_down(window->mlx, MLX_KEY_3))
		window->player->weapon->weapon_type = none;
	clean_weapon(window);
	clean_cross_hair(window);
	if (window->player->weapon->weapon_type == gun)
		return (draw_weapon(window, window->player->weapon->gun_tex[calc_weap_tex(window)]),
			draw_cross_hair(window));
	else if (window->player->weapon->weapon_type == torch)
		return (draw_weapon(window,
				window->player->weapon->torch_tex
				[(window->frame_count % 24) / 3]),
			window->fog = FOG + 5, (void)0);
	else if (window->player->weapon->weapon_type == none)
		window->fog = FOG;
}

int	calc_weap_tex(t_window *window)
{
	int	index;

	index = (float)window->player->weapon->cooldown / WEAPON_COOLDOWN * 5;
	return (index);
}

void	draw_weapon(t_window *window, mlx_texture_t *tex)
{
	int					x_iter;
	int					y_iter;
	int					color;
	const t_vector_int	offset = (t_vector_int){WEAPON_OFFSET_X,
		WEAPON_OFFSET_Y};

	y_iter = -WEAPON_SIZE_Y;
	while (++y_iter < WEAPON_SIZE_Y)
	{
		if (y_iter + offset.y >= HEIGHT)
			continue ;
		x_iter = -WEAPON_SIZE_X;
		while (++x_iter < WEAPON_SIZE_X)
		{
			if (x_iter + offset.x >= WIDTH)
				continue ;
			color = weapon_get_color(
					1 - (WEAPON_SIZE_X - x_iter) / 2.0 / WEAPON_SIZE_X,
					1 - (WEAPON_SIZE_Y - y_iter) / 2.0 / WEAPON_SIZE_Y, tex);
			mlx_put_pixel(window->hud->hud_img,
				x_iter + offset.x, y_iter + offset.y, color);
		}
	}
}

static int	weapon_get_color(double scale_x, double scale_y, mlx_texture_t *tex)
{
	const int	x_pos = tex->width * max(min(scale_x, 1), 0);
	const int	y_pos = tex->height * max(min(scale_y, 1), 0);
	const int	pos = (y_pos * tex->width + x_pos) * tex->bytes_per_pixel;
	const int	color = get_rgba(tex->pixels[pos],
			tex->pixels[pos + 1],
			tex->pixels[pos + 2],
			tex->pixels[pos + 3]);

	return (color);
}

void	draw_cross_hair(t_window *window)
{
	int			x_iter;
	int			y_iter;
	const int	size = 35 + window->player->weapon->cooldown;
	const int	width = 0;
	const int	free_space = 5 + window->player->weapon->cooldown;

	y_iter = -size - 1;
	while (y_iter++ <= size)
	{
		x_iter = -width - 1;
		while (x_iter++ <= width)
			if (abs(y_iter) > free_space)
				mlx_put_pixel(window->hud->hud_img,
					x_iter + WIDTH / 2, y_iter + HEIGHT / 2, CROSSHAIR_COLOR);
	}
	y_iter = -width - 1;
	while (y_iter++ <= width)
	{
		x_iter = -size - 1;
		while (x_iter++ <= size)
			if (abs(x_iter) > free_space)
				mlx_put_pixel(window->hud->hud_img,
					x_iter + WIDTH / 2, y_iter + HEIGHT / 2, CROSSHAIR_COLOR);
	}
}
