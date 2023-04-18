#include <cub3D.h>

static void			draw_vertical_line(t_window *window, t_vector *target,
						int i, t_direction direction);
static t_direction	cast_ray_dda(t_vector *pos, t_vector *dir,
						t_vector *target, t_map *map, t_window *window);

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
		if (ray_iter == 0)
			printf("x: %f   y: %f\n", ft_modf(target.x), ft_modf(target.y));
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

static void	set_dx_and_dy(double *dx, double *dy, t_vector *dir, t_vector *pos, t_map *map, t_window *window)
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

static bool		on_map(double x, double y, t_map *map)
{
	const double	x_pix = x * WIDTH / map->width;
	const double	y_pix = y * HEIGHT / map->height;

	if (x_pix > 0 && x_pix < WIDTH && y_pix > 0 && y_pix < HEIGHT)
		return (true);
	else
		return (false);
}

static	void	set_sx_and_sy(double *sx, double *sy, double dx, double dy, double angle)
{
	if (angle > 0 && angle < M_PI_2)
	{
		*sy = fabs(dy) / sin(angle);
		*sx = fabs(dx) / cos(angle);
	}
	else if (angle >= M_PI_2 && angle < M_PI)
	{
		angle -= M_PI_2;
		*sy = fabs(dy) / cos(angle);
		*sx = fabs(dx) / sin(angle);
	}
	else if (angle < -M_PI_2)
	{
		*sy =(fabs(dy)) / -sin(angle);
		*sx = (fabs(dx)) / -cos(angle);
	}
	else
	{
		angle -= M_PI_2;
		*sy =(fabs(dy)) / -cos(angle);
		*sx = (fabs(dx)) / -sin(angle);
	}
	printf("angle: %f\n", angle);
}

static t_direction	cast_ray_dda(t_vector *pos, t_vector *dir,
	t_vector *target, t_map *map, t_window *window)
{
	double	dx;
	double	dy;
	double	sx;
	double	sy;
	t_vector	temp_dir;
	double	angle;
	t_direction	direction = 0;

	set_vec(target, pos->x, pos->y, pos->z);
	set_vec(&temp_dir, dir->x, dir->y, dir->z);
	while (get_cube_type(target, map) != wall && on_map(target->x, target->y, map))
	{
		set_dx_and_dy(&dx, &dy, dir, target, map, window);
		if (dir->x != 0)
			angle = (atan2(dir->y, dir->x));
		else
			angle = tan(dir->x/ dir->y);
		set_sx_and_sy(&sx, &sy, dx, dy, angle);
		if (sx < sy)
			norm(&temp_dir, sx * 1.01);
		else
			norm(&temp_dir, sy * 1.01);
		set_vec(target, target->x - temp_dir.x, target->y - temp_dir.y, target->z - temp_dir.z);
	}
	const double	eps = 0.02f;
	if (ft_modf(target->y) > 1 - eps)
		return (south);
	if (ft_modf(target->y) < eps)
		return (north);
	if (ft_modf(target->x) > 1 - eps)
		return (east);
	if (ft_modf(target->x) < eps)
		return (west);
	return (east);
}
