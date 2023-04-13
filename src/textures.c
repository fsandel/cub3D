#include <cub3D.h>

double	ft_modf(double num)
{
	return (num - (int)num);
}
uint32_t	get_pixel_from_texture(t_vector *target, t_map *map, int line_height,
			int y, mlx_texture_t *tex)
{
	const double	vert_div = ft_modf(target->x * map->width / WIDTH) * tex->width;
	const double	hor_div = y / line_height * tex->height;
	int				pixel_index;
	int	i;
	u_int32_t		pixel_value;

	i = 0;
	pixel_value = 0;
	pixel_index = (vert_div * WIDTH + hor_div) * 4;
	while (i < 4)
	{
		pixel_value += tex->pixels[pixel_index + i];
		pixel_value = pixel_value << 1;
		i++;
	}
	return (pixel_value);
}
