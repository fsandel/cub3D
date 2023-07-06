#include <cub3D.h>

static void			put_pixel_floor(mlx_image_t *img, t_vector_int pix_pos,
						int base_color, int fog);
static u_int32_t	get_rgba_from_tex(const mlx_texture_t *tex,
						t_vector_int pix_pos, double dis, int fog);

void	draw_vertical_line(t_window *window, t_vector *target,
						int p_x, t_direction direction)
{
	const double		dis = distance_perpendicular(window->player->pos,
			window->player->dir, *target);
	const double		line_height = HEIGHT / dis;
	const int			start = max(((HEIGHT - line_height) / 2), 0);
	const mlx_texture_t	*texture = get_texture(window, target, direction);
	t_vector_int		p;

	p.y = 0;
	p.x = p_x;
	while (p.y < HEIGHT)
	{
		if (p.y < start)
			put_pixel_floor(window->img, p,
				window->map->ceiling_color, window->fog);
		else if (p.y >= start + line_height - 1)
			put_pixel_floor(window->img, p,
				window->map->floor_color, window->fog);
		else
			mlx_put_pixel(window->img, p.x, p.y,
				get_rgba_from_tex(texture,
					(t_vector_int){texture_x_value(texture, target, direction),
					texture_y_value(texture, line_height, p.y, start)},
					dis, window->fog));
		p.y++;
	}
}

static u_int32_t	get_rgba_from_tex(const mlx_texture_t *tex,
				t_vector_int pix_pos, double dis, int fog)
{
	t_rgba			color;
	const int		pos = (pix_pos.y * tex->width + pix_pos.x)
		* tex->bytes_per_pixel;
	const double	brightness = max(1.0 - (dis / fog), 0);

	if (dis > fog)
		return (0x000000ff);
	color.t_color.red = tex->pixels[pos] * brightness;
	color.t_color.green = tex->pixels[pos + 1] * brightness;
	color.t_color.blue = tex->pixels[pos + 2] * brightness;
	color.t_color.alpha = tex->pixels[pos + 3];
	return (color.bytes);
}

static void	put_pixel_floor(mlx_image_t *img, t_vector_int pix_pos,
			int base_color, int fog)
{
	const double	brightness = max(abs(HEIGHT / 2 - pix_pos.y)
			* fog / 4500.0, 0);
	const uint8_t	alpha = base_color & 0xff;
	const uint8_t	red = min(((base_color >> 24) & 0xff) * brightness, 255);
	const uint8_t	green = min(((base_color >> 16) & 0xff) * brightness, 255);
	const uint8_t	blue = min(((base_color >> 8) & 0xff) * brightness, 255);

	base_color = (red << 24) | (green << 16) | (blue << 8) | alpha;
	mlx_put_pixel(img, pix_pos.x, pix_pos.y, base_color);
}
