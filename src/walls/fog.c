#include <cub3D.h>

static void	put_pixel_floor_fog(mlx_image_t *img, t_vector_int pix_pos,
				int base_color, int fog);
static int	get_rgba_from_tex_fog(const mlx_texture_t *tex,
				t_vector_int pix_pos, double dis, int fog);

void	draw_vertical_line_fog(t_window *window, t_vector *target,
				int p_x, t_direction direction)
{
	const double		dis = distance_perpendicular(*window->player->pos,
			*window->player->dir, *target);
	const double		line_height = HEIGHT / dis;
	const int			start = max(((HEIGHT - line_height) / 2), 0);
	const mlx_texture_t	*texture = get_texture(window, target, direction);
	t_vector_int		p;

	p.y = 0;
	p.x = p_x;
	while (p.y < HEIGHT)
	{
		if (p.y < start)
			put_pixel_floor_fog(window->img, p,
				window->map->ceiling_color, window->fog);
		else if (p.y >= start + line_height - 1)
			put_pixel_floor_fog(window->img, p,
				window->map->floor_color, window->fog);
		else
			mlx_put_pixel(window->img, p.x, p.y,
				get_rgba_from_tex_fog(texture,
					(t_vector_int){texture_x_value(texture, target, direction),
					texture_y_value(texture, line_height, p.y, start)},
					dis, window->fog));
		p.y++;
	}
}

static int	get_rgba_from_tex_fog(const mlx_texture_t *tex,
				t_vector_int pix_pos, double dis, int fog)
{
	int				color;
	const int		pos = (pix_pos.y * tex->width + pix_pos.x)
		* tex->bytes_per_pixel;
	const double	brightness = max(1.0 - (dis / fog), 0);

	if (dis > fog)
		return (0x000000ff);
	color = get_rgba(tex->pixels[pos] * brightness,
			tex->pixels[pos + 1] * brightness,
			tex->pixels[pos + 2] * brightness,
			tex->pixels[pos + 3]);
	return (color);
}

static void	put_pixel_floor_fog(mlx_image_t *img, t_vector_int pix_pos,
			int base_color, int fog)
{
	const double	brightness = max(abs(HEIGHT / 2 - pix_pos.y)
			* fog / 4500.0, 0);
	const uint8_t	alpha = base_color & 0xff;
	const uint8_t	red = ((base_color >> 24) & 0xff) * brightness;
	const uint8_t	green = ((base_color >> 16) & 0xff) * brightness;
	const uint8_t	blue = ((base_color >> 8) & 0xff) * brightness;

	if (brightness >= 1)
		mlx_put_pixel(img, pix_pos.x, pix_pos.y, base_color);
	else
	{
		base_color = (red << 24) | (green << 16) | (blue << 8) | alpha;
		mlx_put_pixel(img, pix_pos.x, pix_pos.y, base_color);
	}
}
