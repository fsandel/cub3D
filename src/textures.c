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

int	texture_x_value(mlx_texture_t *tex, t_vector *target, t_map *map,
		t_direction direction)
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
	return ((window_y - start) * tex->height / line_height);
}

int	dim_color(int color, double distance)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = get_red(color);
	green = get_green(color);
	blue = get_blue(color);
	alpha = get_alpha(color);
	alpha = alpha * DARKNESS_FACTOR / distance;
	if (alpha > 255)
		alpha = get_alpha(color);
	return (get_rgba(red, green, blue, alpha));
}
