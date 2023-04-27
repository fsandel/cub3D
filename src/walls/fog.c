#include <cub3D.h>

static void	put_pixel_floor(mlx_image_t *img, int pix_pos_x, int pix_pos_y,
				int base_color);
static int	get_rgba_from_tex_fog(const mlx_texture_t *tex, int x, int y,
				double dis);

void	draw_vertical_line_fog(t_window *window, t_vector *target,
				int p_x, t_direction direction)
{
	const double		dis = distance_perpendicular(*window->player->pos,
			*window->player->dir, *target);
	const double		line_height = HEIGHT / dis;
	const int			start = max(((HEIGHT - line_height) / 2), 0);
	const mlx_texture_t	*texture = get_texture(window, target, direction);
	int					p_y;

	p_y = 0;
	while (p_y < HEIGHT)
	{
		if (p_y < start)
			put_pixel_floor(window->img, p_x, p_y,
				window->map->ceiling_color);
		else if (p_y >= start + line_height - 1)
			put_pixel_floor(window->img, p_x, p_y,
				window->map->floor_color);
		else
			mlx_put_pixel(window->img, p_x, p_y,
				get_rgba_from_tex_fog(texture,
					texture_x_value(texture, target, direction),
					texture_y_value(texture, line_height, p_y, start), dis));
		p_y++;
	}
}

static int	get_rgba_from_tex_fog(const mlx_texture_t *tex, int x, int y,
				double dis)
{
	int				color;
	const int		pos = (y * tex->width + x) * tex->bytes_per_pixel;
	const double	brightness = max(1.0 - (dis / FOG_RANGE), 0);

	color = get_rgba(tex->pixels[pos] * brightness,
			tex->pixels[pos + 1] * brightness,
			tex->pixels[pos + 2] * brightness,
			tex->pixels[pos + 3]);
	return (color);
}

static void	put_pixel_floor(mlx_image_t *img, int pix_pos_x, int pix_pos_y,
			int base_color)
{
	const double	brightness = abs(HEIGHT / 2 - pix_pos_y) / 900.0;
	const uint8_t	alpha = base_color & 0xff;
	const uint8_t	red = ((base_color >> 8) & 0xff) * brightness;
	const uint8_t	green = ((base_color >> 16) & 0xff) * brightness;
	const uint8_t	blue = (base_color >> 24) * brightness;

	base_color = (blue << 24) | (green << 16) | (red << 8) | alpha;
	mlx_put_pixel(img, pix_pos_x, pix_pos_y, base_color);
}
