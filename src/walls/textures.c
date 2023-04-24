#include <cub3D.h>

double	ft_modf(double num)
{
	return (num - (int)num);
}

u_int32_t	get_rgba_from_tex(mlx_texture_t *tex, int x, int y)
{
	int	color;
	int	pos;

	pos = (y * tex->width + x) * tex->bytes_per_pixel;
	color = get_rgba(tex->pixels[pos], tex->pixels[pos + 1],
			tex->pixels[pos + 2], tex->pixels[pos + 3]);
	return (color);
}

int	texture_x_value(mlx_texture_t *tex, t_vector *target, t_direction direction)
{
	if (direction == north || direction == south)
	{
		if (direction == south)
			return (ft_modf(target->x) * tex->width);
		else
			return ((1 - ft_modf(target->x)) * tex->width);
	}
	else
	{
		if (direction == west)
			return (ft_modf(target->y) * tex->width);
		else
			return ((1 - ft_modf(target->y)) * tex->width);
	}
}

int	texture_y_value(mlx_texture_t *tex, int line_height, int window_y,
		int start)
{
	if (line_height >= HEIGHT)
		start = start - ((line_height - HEIGHT) / 2);
	return ((window_y - start) * tex->height / line_height);
}

int	dim_color_floor(int color, int p_y)
{
	const double	darkness = abs(HEIGHT / 2 - p_y);
	const double	dis_factor = darkness / HEIGHT * 2;

	if (dis_factor > 1)
		return (color);
	return (get_rgba(get_red(color) * dis_factor,
			get_green(color) * dis_factor,
			get_blue(color) * dis_factor,
			get_alpha(color)));
}

int	dim_color_walls(int color, double distance)
{
	const double	dis_factor = 2.0f / distance;

	if (dis_factor > 1)
		return (color);
	return (get_rgba(get_red(color) * dis_factor,
			get_green(color) * dis_factor,
			get_blue(color) * dis_factor,
			get_alpha(color)));
}
