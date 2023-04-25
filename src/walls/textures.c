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
	uint8_t alpha = color & 0xff;
	uint8_t red = (color >> 8) & 0xff;
	uint8_t green = (color >> 16) & 0xff;
	uint8_t blue = color >> 24;

	double brightness = abs(HEIGHT / 2 - p_y) / 900.0;

	uint8_t new_red = red * brightness;
	uint8_t new_green = green * brightness;
	uint8_t new_blue = blue * brightness;

	return (new_blue << 24) | (new_green << 16) | (new_red << 8) | alpha;
}

int	dim_color_walls(int color, double distance)
{
	uint8_t alpha = color & 0xff;
	uint8_t red = (color >> 8) & 0xff;
	uint8_t green = (color >> 16) & 0xff;
	uint8_t blue = color >> 24;

	double brightness = max(1.0 - (distance / 6.0), 0);

	uint8_t new_red = red * brightness;
	uint8_t new_green = green * brightness;
	uint8_t new_blue = blue * brightness;

	return (new_blue << 24) | (new_green << 16) | (new_red << 8) | alpha;
}
