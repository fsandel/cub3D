#include <cub3D.h>

double	ft_modf(double num)
{
	return (num - (int)num);
}

// uint32_t	get_pixel(mlx_texture_t *tex, int x, int y)
// {
// 	int		i = 0;
// 	u_int32_t pixel;

// 	pixel = 0;
// 	while (i < 4)
// 	{
// 		pixel += tex->pixels[(y * tex->width + x) * 4 + i];
// 		pixel = pixel << 0;
// 		//pixel *= 256;
// 		i++;
// 	}
// 	return (pixel);
// }

uint32_t	get_pixel(mlx_texture_t *tex, int x, int y)
{
	u_int32_t color;
	const int red = tex->pixels[(y * tex->width + x) * 4 + 0];
	const int green = tex->pixels[(y * tex->width + x) * 4 + 1];
	const int blue = tex->pixels[(y * tex->width + x) * 4 + 2];
	const int alpha = tex->pixels[(y * tex->width + x) * 4 + 3];

	color = get_rgba(red, green, blue, alpha);
	return (color);
}

uint32_t	get_pixel_from_texture(t_window *window, t_vector *target, t_map *map, int line_height,
			int y, mlx_texture_t *tex, int x)
{
	const double	vert_div = ft_modf(target->x * map->width * tex->width)/ WIDTH;
	const double	hor_div = y * tex->height / line_height;
	int				pixel_index;
	int	i;
	u_int32_t		pixel_value;

	i = 0;
	pixel_value = get_pixel(tex, hor_div, vert_div);
	//ft_memcpy(&window->img->pixels[(int)(vert_div + hor_div)], )
	return (pixel_value);
}

u_int32_t	get_rgba_from_tex(mlx_texture_t *tex, int x, int y)
{
	int color;
	int pos;

	pos = (y * tex->width + x) * tex->bytes_per_pixel;
	color = get_rgba(tex->pixel[pos], tex->pixel[pos + 1], tex->pixel[pos + 2], tex->pixel[pos + 3]);
	return (color);
}

//check if no weird float/int stuff happens
int texture_x_value(mlx *tex, t_vector *target, t_map *map, t_direction direction)
{
	//if (direction == west || direction == east)
	if (direction == north || direction == south)
		return (target->x * map->width / WIDTH);
	else
		return (target->y * map->height / HEIGHT);
}

//check if no weird float/int stuff happens
int texture_y_value(mlx_texture_t *tex,  int line_height, int window_y, int start)
{
	return ((window_y - start) * tex->height / line_height);
}
