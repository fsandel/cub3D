#include <cub3D.h>

static void			draw_vertical_line(t_window *window, t_vector *target,
						int i, t_direction direction);
static t_direction	cast_ray_dda(t_vector *pos, t_vector *dir,
						t_vector *target, t_map *map);

void	draw_scene(t_window *window)
{
	t_vector			target;
	t_vector			ray_dir;
	const double		fov = (FOV * M_PI) / 180;
	int					ray_iter;
	t_direction			direction;

	ray_iter = -WIDTH / 2;
	while (ray_iter < WIDTH / 2)
	{
		rotate_hor_f(window->player->dir, &ray_dir, ray_iter * fov / WIDTH);
		direction = cast_ray_dda(window->player->pos, &ray_dir,
				&target, window->map, window);
		draw_vertical_line(window, &target, ray_iter + WIDTH / 2, direction);
		ray_iter++;
	}
}

static void	draw_vertical_line(t_window *window, t_vector *target, int p_x,
				t_direction direction)
{
	const double	line_height = HEIGHT * 1 / distance_perpendicular(
			*window->player->pos, *window->player->dir, *target);
	const int		start = max(((HEIGHT - line_height) / 2), 0);
	int				p_y;
	uint32_t		pix;
	t_vector		tex;

	p_y = 0;
	while (p_y < HEIGHT)
	{
		if (p_y < start)
			mlx_put_pixel(window->img, p_x, p_y++, window->map->ceiling_color);
		else if (p_y >= start + line_height - 1)
			mlx_put_pixel(window->img, p_x, p_y++, window->map->floor_color);
		else
		{
			tex.x = texture_x_value(window->map->textures[direction],
					target, direction);
			tex.y = texture_y_value(window->map->textures[direction],
					line_height, p_y, start);
			pix = get_rgba_from_tex(window->map->textures[direction],
					tex.x, tex.y);
			mlx_put_pixel(window->img, p_x, p_y++, pix);
		}
	}
}

static void	set_dx_and_dy(double *dx, double *dy, t_vector *dir, t_vector *pos)
{
	if (dir->x >= 0 && dir->y >= 0)
	{
		*dx = -ft_modf(pos->x);
		*dy = -ft_modf(pos->y);
	}
	else if (dir->x >= 0 && dir->y < 0)
	{
		*dx = -ft_modf(pos->x);
		*dy = 1 - ft_modf(pos->y);
	}
	else if (dir->x < 0 && dir->y >= 0)
	{
		*dx = 1 - ft_modf(pos->x);
		*dy = -ft_modf(pos->y);
	}
	else
	{
		*dx = 1 - ft_modf(pos->x);
		*dy = 1 - ft_modf(pos->y);
	}
}

//maybe rethink this in the future, it works for right now
//but it doesnt seem perfect
static t_direction	get_direction_of_target(t_vector target)
{
	const double	eps = 0.02f;

	if (ft_modf(target.y) > 1 - eps)
		return (south);
	else if (ft_modf(target.y) < eps)
		return (north);
	else if (ft_modf(target.x) > 1 - eps)
		return (east);
	else
		return (west);
}

static t_direction	cast_ray_dda(t_vector *pos, t_vector *dir,
	t_vector *target, t_map *map)
{
	double		dx;
	double		dy;
	double		sx;
	double		sy;
	double		angle;

	set_vec(target, pos->x, pos->y, pos->z);
	while (get_cube_type(target, map) != wall)
	{
		set_dx_and_dy(&dx, &dy, dir, target);
		angle = (atan2(dir->y, dir->x));
		sx = dx / -cos(angle);
		sy = dy / -sin(angle);
		if (sx < sy)
			norm(dir, sx * 1.01);
		else
			norm(dir, sy * 1.01);
		set_vec(target, target->x - dir->x, target->y - dir->y,
			target->z - dir->z);
	}
	norm(dir, 1);
	return (get_direction_of_target(*target));
}
