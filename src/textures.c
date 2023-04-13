#include <cub3D.h>

double	ft_modf(double num)
{
	return (num - (int)num);
}

uint32_t	get_pixel(mlx_texture_t *tex, int x, int y)
{
	int		i = 0;
	u_int32_t pixel;

	pixel = 0;
	while (i < 4)
	{
		pixel += tex->pixels[(y * tex->width + x) * 4 + i];
		pixel = pixel << 0;
		//pixel *= 256;
		i++;
	}
	return (pixel);
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
	//pixel_value = get_pixel(tex, hor_div, vert_div);
	//ft_memcpy(&window->img->pixels[(int)(vert_div + hor_div)], )
	return (0);
}
