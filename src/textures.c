#include <cub3D.h>

double	ft_modf(double num)
{
	return (num - (int)num);
}

u_int32_t	get_rgba_from_tex(mlx_texture_t *tex, int x, int y)
{
	int color;
	int pos;

	pos = (y * tex->width + x) * tex->bytes_per_pixel;
	color = get_rgba(tex->pixels[pos], tex->pixels[pos + 1], tex->pixels[pos + 2], tex->pixels[pos + 3]);
	return (color);
}

//check if no weird float/int stuff happens
int texture_x_value(mlx_texture_t *tex, t_vector *target, t_map *map, t_direction direction)
{
	if (direction == north || direction == south)
	//if (direction == west || direction == east)
		return (ft_modf(target->x * map->width / WIDTH) * tex->width);
	else
		return (ft_modf(target->y * map->height / HEIGHT) * tex->height);
}

//check if no weird float/int stuff happens
int texture_y_value(mlx_texture_t *tex,  int line_height, int window_y, int start)
{
	return ((window_y - start) * tex->height / line_height);
}
