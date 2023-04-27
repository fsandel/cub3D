#include <cub3D.h>

u_int32_t	get_rgba_from_tex(const mlx_texture_t *tex, int x, int y)
{
	int	color;
	int	pos;

	pos = (y * tex->width + x) * tex->bytes_per_pixel;
	color = get_rgba(tex->pixels[pos], tex->pixels[pos + 1],
			tex->pixels[pos + 2], tex->pixels[pos + 3]);
	return (color);
}

int	texture_x_value(const mlx_texture_t *tex, t_vector *target,
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

int	texture_y_value(const mlx_texture_t *tex, int line_height, int window_y,
		int start)
{
	if (line_height >= HEIGHT)
		start = start - ((line_height - HEIGHT) / 2);
	return ((window_y - start) * tex->height / line_height);
}

mlx_texture_t	*get_texture(t_window *window, t_vector *target,
							t_direction direction)
{
	if (get_cube_type(target, window->map) == wall)
		return (window->map->textures[direction]);
	else if (get_cube_type(target, window->map) == door_closed)
		return (window->map->door);
	else
		return (window->map->textures[north]);
}
