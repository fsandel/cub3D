#include <cub3D.h>

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
	const t_cube_type	cube_type = get_cube_type(target, window->map);

	if (cube_type == wall)
		return (window->map->textures[direction]);
	else if (cube_type == door_closed)
		return (window->map->door_tex);
	else if (cube_type == ammo_full)
		return (window->ammo_tex[0]);
	else if (cube_type == ammo_empty)
		return (window->ammo_tex[1]);
	else if (cube_type == health_full)
		return (window->health_tex[0]);
	else if (cube_type == health_empty)
		return (window->health_tex[1]);
	else if (cube_type == exit_cube && window->frame_count % 64 < 32)
		return (window->exit_tex[0]);
	else if (cube_type == exit_cube && window)
		return (window->exit_tex[1]);
	else if (cube_type == destructible)
		return (window->destructible_tex);
	else
		return (window->map->textures[north]);
}
